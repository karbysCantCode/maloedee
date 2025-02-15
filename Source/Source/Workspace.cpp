#include "Workspace.h"

#include <assert.h>
#include <algorithm> // for index buffer index offset
#include <unordered_map>

Workspace::Workspace(const float ScreenWidth, const float ScreenHeight)
	: m_ScreenWidth(ScreenWidth)
	, m_ScreenHeight(ScreenHeight)

	, m_IndexBuffer(new IndexBuffer(nullptr, 0, GL_DYNAMIC_DRAW))
	, m_VertexBuffer(new VertexBuffer(nullptr, 0, GL_DYNAMIC_DRAW))

	, m_Program(glCreateProgram())
	, m_FragmentShader(std::string(SHADERS "3DFragment.shader")) // SHADERS is a macro string, or something, defined in cmakelists if you're curious
	, m_VertexShader(std::string(SHADERS "3DVertex.shader"))
	, m_ShaderStorageBuffer(new ShaderStorageBuffer(nullptr, 0, 0, GL_DYNAMIC_DRAW))

	, m_Projection(glm::perspective(glm::radians(90.0f), ScreenWidth / ScreenHeight, 0.1f, 1000.0f))
{
	m_VertexBufferLayout.Push<float>(3); // position floats
	m_VertexBufferLayout.Push<float>(4); // color floats
	m_VertexBufferLayout.Push<unsigned int>(1); // model ID
	m_VertexArray.AddBuffer(*m_VertexBuffer, m_VertexBufferLayout);

	glAttachShader(m_Program, m_VertexShader.shaderID);
	glAttachShader(m_Program, m_FragmentShader.shaderID);
	glLinkProgram(m_Program);
	glValidateProgram(m_Program);
	glUseProgram(m_Program);

	m_UniformHelper.BindProgram(m_Program);
	m_UniformHelper.SetUniformMat4f("u_Projection", m_Projection);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1000.0f));
	m_UniformHelper.SetUniformMat4f("u_View", view);
	glUseProgram(0);
}

Workspace::~Workspace()
{
}

void Workspace::Recompile3DInstanceData() // recompile on gpu?
{
	m_VertexData.resize(0);
	m_VertexOrder.resize(0);
	m_ObjectPositions.resize(0);

	for (unsigned int Index = 0; Index < m_3DInstances.size(); Index++) // do a loop to resize only once?
	{
		Instance* instanceInstance = m_3DInstances[Index];
		instanceInstance->Changed = false;
		instanceInstance->PositionChanged = false;

		ObjectInstance* objInstance = static_cast<ObjectInstance*>(instanceInstance);
		objInstance->ObjectID = Index;

		const unsigned int VERTEX_DATA_ENTRIES = m_VertexData.size();
		m_ObjectIDFirstDataEntry[Index] = VERTEX_DATA_ENTRIES;
		m_ObjectIDFirstOrderEntry[Index] = m_VertexOrder.size();

		ObjectInstance::VertexDataOrderPair newObjectData = objInstance->GetObjectData();

		//m_VertexData.resize(m_VertexData.size() + newObjectData.vertexData.size()); // dont need resize for insert, insert does it itself

		m_VertexData.insert(m_VertexData.end(), newObjectData.vertexData.begin(), newObjectData.vertexData.end());


		const unsigned int VERTICIES_IN_DATA = VERTEX_DATA_ENTRIES / m_VertexBufferLayout.GetNumberOfIndividualElements();

		std::transform(newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end(), newObjectData.vertexOrder.begin(),
			[VERTICIES_IN_DATA](int x) { return x + VERTICIES_IN_DATA; });
		m_VertexOrder.insert(m_VertexOrder.end(), newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end());

		m_ObjectPositions.push_back(glm::vec4(objInstance->GetPosition(),1.0f));
	}

	m_VertexBuffer->SetBuffer(m_VertexData.data(), m_VertexData.size() * (m_VertexBufferLayout.GetStride() / m_VertexBufferLayout.GetNumberOfIndividualElements()), GL_DYNAMIC_DRAW);
	m_IndexBuffer->SetBuffer(m_VertexOrder.data(), m_VertexOrder.size(), GL_DYNAMIC_DRAW);
	m_ShaderStorageBuffer->SetBuffer(m_ObjectPositions.data(), m_ObjectPositions.size() * sizeof(glm::vec4), GL_DYNAMIC_DRAW);
}


Instance* Workspace::NewInstance(Instance::InstanceType instanceType) // thiss looks evil - actually im going to fix it - OMG A CAT just ran past my window
{
	Instance* newInstance = nullptr;

	switch (instanceType)
	{
	case Instance::OBJECT:
	{
		newInstance = new ObjectInstance(m_ObjectChanged, m_RecompileObjectData, m_3DInstances.size());
		m_3DInstances.push_back(newInstance);
		
		m_RecompileObjectData = true;

		//ObjectInstance* object = static_cast<ObjectInstance*>(newInstance);
		//object->ObjectID = m_3DInstances.size();
		//
		//m_3DInstances.push_back(static_cast<ObjectInstance*>(newInstance));
		//
		//m_ObjectIDFirstDataEntry[object->ObjectID] = m_VertexData.size();
		//m_ObjectIDFirstOrderEntry[object->ObjectID] = m_VertexOrder.size();
		//
		//// adding new vertex data
		//
		//ObjectInstance::VertexDataOrderPair newObjectData = object->GetObjectData();
		//m_VertexData.resize(m_VertexData.size() + newObjectData.vertexData.size());
		//
		//m_VertexData.insert(m_VertexData.end()
		//	, newObjectData.vertexData.begin(), newObjectData.vertexData.end());
		//
		//// adding new order data
		//
		//const unsigned int VERTEX_ORDER_ARRAY_SIZE = m_VertexOrder.size(); // apply offset on gpu for large assets?
		//
		//std::transform(newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end(), newObjectData.vertexOrder.begin(),
		//	[VERTEX_ORDER_ARRAY_SIZE](int x) { return x + VERTEX_ORDER_ARRAY_SIZE; });
		//
		//m_VertexOrder.insert(m_VertexOrder.end()
		//	, newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end());
		//
		// dont think i need the above? it does the same operations on cpu arrays as recompiling does, but it doesnt write to buffers, so recompiling would work better?
	}
	break;

	default:
		// INVALID INSTANCE TYPE SOMEHOW?? nah how do you do this
		// if you trigger this hit me up! i wanna know
		assert(false);
		break;
	}
	return newInstance;
}

void Workspace::Destroy(Instance* instance)
{
	delete instance;
	Recompile3DInstanceData();
}

void Workspace::Update()
{
	if (m_RecompileObjectData)
	{
		std::cout << "recompile" << std::endl;
		m_RecompileObjectData = false;
		Recompile3DInstanceData();
	}
	else if (m_ObjectChanged)
	{
		std::cout << "obj update" << std::endl;
		m_ObjectChanged = false;
		for (const auto& object : m_3DInstances)
		{
			if (typeid(*object) == typeid(ObjectInstance))
			{
				ObjectInstance* obj = static_cast<ObjectInstance*>(object);
				std::cout << obj->Changed << std::endl;
				if (obj->Changed) 
				{
					obj->Changed = false;

					ObjectInstance::VertexDataOrderPair newObjectData = obj->GetObjectData();

					std::memcpy(&m_VertexData[m_ObjectIDFirstDataEntry[obj->ObjectID]], newObjectData.vertexData.data(), newObjectData.vertexData.size() * m_VertexBufferLayout.GetStride());

					const unsigned int firstEntryIndex = m_ObjectIDFirstOrderEntry[obj->ObjectID];// apply offset on gpu for large assets?

					std::transform(newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end(), newObjectData.vertexOrder.begin(),
						[firstEntryIndex](int x) { return x + firstEntryIndex; });

					std::memcpy(&m_VertexOrder[firstEntryIndex], newObjectData.vertexOrder.data(), newObjectData.vertexOrder.size() * sizeof(unsigned int));
				}

				if (object->PositionChanged)
				{
					object->PositionChanged = false;
					std::cout << "theoretically updating the shader storage :shrug:" << std::endl;
					const glm::vec4 position(obj->GetPosition(), 1.0f);
					m_ShaderStorageBuffer->UpdateBufferSection(&position, sizeof(glm::vec4), sizeof(glm::vec4) * obj->ObjectID);
					GLAssertError();
				}
			}
			else
			{
				assert(false);
			}
		}
	}
}

void Workspace::Render()
{
	glUseProgram(m_Program);
	m_VertexArray.Bind();
	m_IndexBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}