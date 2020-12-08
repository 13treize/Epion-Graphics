#include "../Epion12.h"
#include "ShaderGenerate.h"


namespace
{
	/*
		¡‰ñ‚ÍAinclude‚·‚é‚©‚çŠÖ”ŒÄ‚Ño‚µÁ‹
	*/
	bool cnt;
	int counts=0;
}

namespace epion
{
	std::vector<int>	NodeShaderManager::current_id;
	std::vector<int>	NodeShaderManager::get_id;

	int	NodeShaderManager::m_space_type;
	std::string	NodeShaderManager::m_space;

	int	NodeShaderManager::m_space_count;
	int	NodeShaderManager::texture2d_count;

	std::string	NodeShaderManager::function_str;

	std::list<std::string>	NodeShaderManager::create_str;
	std::list<std::string>	NodeShaderManager::node_create_str;

	//std::vector<std::unique_ptr<Node::NodeBase>>	NodeShaderManager::nodes;
	//std::vector<Node::NodeLink>	NodeShaderManager::links;
	std::vector	<std::string>	NodeShaderManager::variable;
	std::map	<std::string, int>	NodeShaderManager::shader_function;

	NodeShaderManager::NodeShaderManager()
	{
	}

	NodeShaderManager::~NodeShaderManager()
	{
	}

	void	NodeShaderManager::Generate(const std::string& file_path)
	{
		shader_function.clear();
		create_str.clear();
		node_create_str.clear();

		shader_function.emplace("FIRST", 0);
		variable.clear();
		std::ofstream	ofs(file_path);
		Init();
		ofs << PSInputGenerate();
		//‰½‚©‚µ‚ç‚Å§Œä
		ofs << CBuffer0SetUp();
		ofs << CBuffer1SetUp();
		ofs << CBuffer2SetUp();
		ofs << CBuffer3SetUp();

		//Node‚ÌŠÖ”‚ğ¶¬
		//ofs << FuncSetup();

		//PixelShader
		ofs << MainFunctionBegin();
		ofs << EventBegin();
		ofs << CBuffer0Create();
		ofs << Create();
		ofs << EventEnd();


		ofs.close();


	}

	void	NodeShaderManager::Init()
	{
		current_id = {};
		get_id = {};
		cnt = false;

		//node_id.resize(nodes.size());
		m_space = "";
		m_space_count = 0;
		texture2d_count = 0;
		create_str.clear();
	}

	std::string	NodeShaderManager::CBuffer0SetUp()
	{
		return
			"cbuffer TimeCBuffer : register(b0)\n"
			"{\n"
			"    float4 Time;\n"
			"    float2 ScreenSize;\n"
			"    float2 Dummy0;\n"
			"};\n";
	}
	std::string	NodeShaderManager::CBuffer1SetUp()
	{
		return
			"cbuffer LightCBuffer : register(b1)\n"
			"{\n"
			"    float4 LightColor;\n"
			"    float4 LightDir;\n"
			"    float4 AmbientColor;\n"
			"};\n";
	}
	std::string	NodeShaderManager::CBuffer2SetUp()
	{
		return
			"cbuffer CameraCBuffer : register(b2)\n"
			"{\n"
			"    float4 Pos;\n"
			"    float4 Target;\n"
			"    float4 Up;\n"
			"};\n";

	}
	std::string	NodeShaderManager::CBuffer3SetUp()
	{
		return
			"cbuffer WorldCBuffer : register(b3)\n"
			"{\n"
			"    row_major float4x4 WorldViewProjection;\n"
			"    row_major float4x4 World;\n"
			"};\n";
	}


	std::string	NodeShaderManager::CBuffer0Create()
	{
		return
			"    float Time_ =Time.x;\n"
			"    float Sin_Time_ =sin(Time.x);\n"
			"    float Cos_Time_ =cos(Time.x);\n";
	}

	void	NodeShaderManager::NodeCreate()
	{
		counts++;
		get_id.clear();
		//linkdara‚ğ‘–¸
		//for (auto& li : links)
		//{
		//	for (auto& c_id : current_id)
		//	{
		//		//©•ª‚Ìid‚ğŒ©‚Â‚¯‚½‚È‚ç
		//		if (li.GetInputID() == c_id)
		//		{
		//			//”h¶æ‚Ìid‚ğŠi”[
		//			get_id.push_back(li.GetOutputID());
		//		}
		//	}
		//}
		////”h¶æ‚ğ¶¬
		//for (auto& ids : get_id)
		//{
		//	create_str.push_front(nodes[ids]->get_function_call_str() + "\n");
		//}
		current_id.clear();
		//”h¶‚ğæ“¾
		current_id = get_id;

		if (!current_id.empty())
		{
			NodeCreate();
		}
		return;
	}

	std::string	NodeShaderManager::Create()
	{
		std::string	ret_str;
		//MasterNode‚ğŒ©‚Â‚¯‚Ä‚»‚Á‚©‚ç’H‚Á‚Ä¶¬

		//for (auto& n : nodes)
		//{
		//	if (typeid(*n) == typeid(Node::UnlitMasterNode) ||
		//		typeid(*n) == typeid(Node::PBRMasterNode))
		//	{
		//		create_str.push_back(float4Generate2("flag_color", n->get_function_call_str()));
		//		current_id.push_back(n->m_ID);
		//		break;
		//	}
		//}

		NodeCreate();

		for (const auto& c : create_str)
		{
			ret_str += c;
		}

		ret_str += ReturnEvent("flag_color");
		return	ret_str;
	}

	std::string	NodeShaderManager::FuncSetup()
	{
		function_str = "";
		//texture
		//for (auto&n : nodes)
		//{
		//	if (typeid(*n) == typeid(Node::SamplerTexture2DNode))
		//	{
		//		function_str += n->GetFunctionDefStr() + "(t" + std::to_string(texture2d_count) + ");\n";
		//		texture2d_count++;
		//	}
		//}

		////Sampler State
		//for (auto& n : nodes)
		//{
		//	if (typeid(*n) == typeid(Node::SamplerStateNode) ||
		//		typeid(*n) == typeid(Node::Texture2DNode))
		//	{
		//		n->ShaderUpdate(nodes, links);
		//		function_str += n->GetFunctionDefStr() + "\n";
		//	}
		//}

		////function
		//for (auto& n : nodes)
		//{
		//	auto it = shader_function.find(n->m_Name);
		//	if (it != shader_function.end() ||
		//		typeid(*n) == typeid(Node::SamplerStateNode) ||
		//		typeid(*n) == typeid(Node::Texture2DNode))
		//	{
		//		continue;
		//	}
		//	else
		//	{
		//		function_str += n->GetFunctionDefStr() + "\n";
		//		shader_function.emplace(n->m_Name, 0);
		//	}
		//}
		return	function_str;
	}


	void	NodeShaderManager::SetSpace()
	{
		switch (m_space_type)
		{
		case 0:	m_space = "";		break;
		case 1:	m_space = "	";		break;
		case 2:	m_space = "    ";	break;
		}
	}

	std::string	NodeShaderManager::CallUV()
	{
		return	"input.uv";
	}

	std::string	NodeShaderManager::EventBegin()
	{
		std::string	ret_str = m_space + "{\n";
		//m_space += "    ";
		m_space_count++;
		return	ret_str;
	}

	std::string	NodeShaderManager::EventEnd()
	{
		m_space = "";
		m_space_count--;
		for (int i = 0; m_space_count < i; i++)
		{
			m_space += "    ";
		}
		std::string	ret_str = m_space + "}\n";
		return	ret_str;
	}

	std::string	NodeShaderManager::EventEnd2()
	{
		m_space = "";
		m_space_count--;
		for (int i = 0; m_space_count < i; i++)
		{
			m_space += "    ";
		}
		std::string	ret_str = "};\n";
		return	ret_str;
	}

	std::string	NodeShaderManager::PSInputGenerate()
	{
		std::string	ret_str;
		ret_str = "struct PSInput\n";
		ret_str += EventBegin();
		ret_str += m_space + "float4 position : SV_POSITION;\n";
		ret_str += m_space + "float4 normal : NORMAL;\n";
		ret_str += m_space + "float2 uv : TEXCOORD0;\n";
		ret_str += m_space + "float4 wpos : TEXCOORD1;\n";
		ret_str += m_space + "float4 lpos : TEXCOORD2;\n";
		ret_str += EventEnd2();
		return	ret_str;
	}

	std::string	NodeShaderManager::MainFunctionBegin()
	{
		std::string	function_name = "float4 PS(PSInput input) : SV_TARGET\n";

		return	function_name;
	}

	std::string	NodeShaderManager::float4Generate2(std::string	var_str, std::string	init_str)
	{
		std::string	ret_str = m_space + "float4 " + var_str + init_str;
		return	ret_str;
	}

	std::string	NodeShaderManager::ReturnEvent(std::string retuern_color_str)
	{
		std::string	ret_str = m_space + "return " + retuern_color_str + ";\n";
		return	ret_str;
	}

}