#include "RenderGroup.h"



void RenderGroup::Recompile3DInstanceData()
{
	m_VertexData.resize(0);
	m_VertexOrder.resize(0);
	const unsigned int objectCount = m_3DInstances.size();
	m_SSBOData.resize(shaderStorageBuffer->GetStride() * objectCount);

	for (unsigned int Index = 0; Index < objectCount; Index++) // do a loop to resize only once?
	{
		Instance* instanceInstance = m_3DInstances[Index];
		instanceInstance->Changed = false;
		instanceInstance->SSBOUpdate = false;

		ObjectInstance* objInstance = static_cast<ObjectInstance*>(instanceInstance);
		objInstance->ObjectID = Index;

		const unsigned int VERTEX_DATA_ENTRIES = m_VertexData.size();
		m_ObjectIDFirstDataEntry[Index] = VERTEX_DATA_ENTRIES;
		m_ObjectIDFirstOrderEntry[Index] = m_VertexOrder.size();

		ObjectInstance::VertexDataOrderPair newObjectData = objInstance->GetObjectData();

		//m_VertexData.resize(m_VertexData.size() + newObjectData.vertexData.size()); // dont need resize for insert, insert does it itself

		m_VertexData.insert(m_VertexData.end(), newObjectData.vertexData.begin(), newObjectData.vertexData.end());


		const unsigned int VERTICIES_IN_DATA = VERTEX_DATA_ENTRIES / vertexBufferLayout.GetNumberOfIndividualElements();

		std::transform(newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end(), newObjectData.vertexOrder.begin(),
			[VERTICIES_IN_DATA](int x) { return x + VERTICIES_IN_DATA; });
		m_VertexOrder.insert(m_VertexOrder.end(), newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end());

		// SSBO ASSIGNING

		const glm::vec3 objPosition = objInstance->GetPosition();
		const glm::vec4 objColor = objInstance->GetColor();
		static_assert(false); // continue changing stuff uhmmm yeah
		std::vector<float> tempData =
		{
			objPosition.x,
			objPosition.y,
			objPosition.z,
			objColor.r,
			objColor.g,
			objColor.b,
			objColor.a
		};

		std::memcpy(&m_SSBOData[Index * shaderStorageBuffer->GetStride()], SSBO_DATA, shaderStorageBuffer->GetStride() * sizeof(float));
	}
	m_VertexBuffer->SetBuffer(m_VertexData.data(), m_VertexData.size() * (vertexBufferLayout.GetStride() / vertexBufferLayout.GetNumberOfIndividualElements()), GL_DYNAMIC_DRAW);
	m_IndexBuffer->SetBuffer(m_VertexOrder.data(), m_VertexOrder.size(), GL_DYNAMIC_DRAW);
	shaderStorageBuffer->SetBuffer(m_SSBOData.data(), m_SSBOData.size() * sizeof(float), GL_DYNAMIC_DRAW);
}

void RenderGroup::RecompileProgram()
{
	if (m_Program != 0)
	{
		glDeleteProgram(m_Program);
	}
	if (m_VertexShader.shaderID != 0)
	{
		glDeleteShader(m_VertexShader.shaderID);
	}
	if (m_FragmentShader.shaderID != 0)
	{
		glDeleteShader(m_FragmentShader.shaderID);
	}
	m_VertexShader.compileShader(m_VertexShader.parseShaderFile());
	m_FragmentShader.compileShader(m_FragmentShader.parseShaderFile());
	glAttachShader(m_Program, m_VertexShader.shaderID);
	glAttachShader(m_Program, m_FragmentShader.shaderID);
	glLinkProgram(m_Program);
	glValidateProgram(m_Program);
	glUseProgram(m_Program);
	glDeleteShader(m_VertexShader.shaderID);
	glDeleteShader(m_FragmentShader.shaderID);
}

RenderGroup::RenderGroup(const float ScreenWidth, const float ScreenHeight, const float FOV)
	: m_ScreenWidth(ScreenWidth)
	, m_ScreenHeight(ScreenHeight)

	, m_IndexBuffer(new IndexBuffer(nullptr, 0, GL_DYNAMIC_DRAW))
	, m_VertexBuffer(new VertexBuffer(nullptr, 0, GL_DYNAMIC_DRAW))

	, m_Program(glCreateProgram())
	, shaderStorageBuffer(new ShaderStorageBuffer(nullptr, 0, 0, GL_DYNAMIC_DRAW))

	, m_Projection(glm::perspective(glm::radians(FOV), ScreenWidth / ScreenHeight, 0.1f, 1000.0f))
{
	vertexBufferLayout.Push<float>(3); // position floats
	vertexBufferLayout.Push<float>(3); // face normal floats
	vertexBufferLayout.Push<float>(1); // model ID THE FUCKING EVIL LINE BRO WHY DOES IT CAST THE VALUE, I THOUGHT IT WOULD JUST TELL HOW TO INTERPRET
	m_VertexArray.AddBuffer(*m_VertexBuffer, vertexBufferLayout);

	m_UniformHelper.BindProgram(m_Program);
	m_UniformHelper.SetUniformMat4f("u_Projection", m_Projection);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1000.0f));
	m_UniformHelper.SetUniformMat4f("u_View", view);
	glUseProgram(0);
}

RenderGroup::~RenderGroup()
{
	delete m_IndexBuffer;
	delete m_VertexBuffer;
	delete shaderStorageBuffer;
}

void RenderGroup::UpdateVertexArray()
{
	m_VertexArray.AddBuffer(*m_VertexBuffer, vertexBufferLayout);
}

Instance* RenderGroup::NewInstance(Instance::InstanceType instanceType)
{
	Instance* newInstance = nullptr;

	switch (instanceType)
	{
	case Instance::OBJECT:
	{
		newInstance = new ObjectInstance(m_ObjectChanged, m_RecompileObjectData, m_NextFree3DObjectID);
		m_3DInstances.push_back(newInstance);
		m_NextFree3DObjectID++;
		m_RecompileObjectData = true;
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

void RenderGroup::Destroy(Instance* instance)
{
	auto it = std::find(m_3DInstances.begin(), m_3DInstances.end(), instance);
	if (it != m_3DInstances.end()) {
		m_3DInstances.erase(it);  // Remove the pointer from vector
		delete instance;       // Free memory
	}
	m_RecompileObjectData = true;
}

void RenderGroup::Update()
{
	if (m_RecompileObjectData)
	{
		m_RecompileObjectData = false;
		Recompile3DInstanceData();
	}
	else if (m_ObjectChanged)
	{
		m_ObjectChanged = false;
		for (const auto& object : m_3DInstances)
		{
			if (typeid(*object) == typeid(ObjectInstance))
			{
				ObjectInstance* obj = static_cast<ObjectInstance*>(object);
				if (obj->Changed)
				{
					obj->Changed = false;

					ObjectInstance::VertexDataOrderPair newObjectData = obj->GetObjectData();

					std::memcpy(&m_VertexData[m_ObjectIDFirstDataEntry[obj->ObjectID]], newObjectData.vertexData.data(), newObjectData.vertexData.size() * vertexBufferLayout.GetStride());

					const unsigned int firstEntryIndex = m_ObjectIDFirstOrderEntry[obj->ObjectID];// apply offset on gpu for large assets?

					std::transform(newObjectData.vertexOrder.begin(), newObjectData.vertexOrder.end(), newObjectData.vertexOrder.begin(),
						[firstEntryIndex](int x) { return x + firstEntryIndex; });

					std::memcpy(&m_VertexOrder[firstEntryIndex], newObjectData.vertexOrder.data(), newObjectData.vertexOrder.size() * sizeof(unsigned int));
				}

				if (obj->SSBOUpdate)
				{
					obj->SSBOUpdate = false;
					const glm::vec3 objPosition = obj->GetPosition();
					const glm::vec4 objColor = obj->GetColor();

					const float SSBO_DATA[shaderStorageBuffer->GetStride()] =
					{
						objPosition.x,
						objPosition.y,
						objPosition.z,

						objColor.r,
						objColor.g,
						objColor.b,
						objColor.a
					};

					constexpr unsigned int SSBO_ENTRY_IN_BYTES = shaderStorageBuffer->GetStride() * sizeof(float);
					shaderStorageBuffer->UpdateBufferSection(&SSBO_DATA, SSBO_ENTRY_IN_BYTES, SSBO_ENTRY_IN_BYTES * obj->ObjectID);
				}
			}
			else
			{
				assert(false);
			}
		}
	}
}

void RenderGroup::Render()
{
	glUseProgram(m_Program);
	m_VertexArray.Bind();
	m_IndexBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}
