#include"ImuDecoder.h"
using namespace RobotSDK_Module;

//If you need to use extended node, please uncomment below and comment the using of default node
//USE_EXTENDED_NODE(ExtendedNodeClass[,...])
USE_DEFAULT_NODE

//=================================================
//Uncomment below PORT_DECL and set input node class name
//PORT_DECL(0, InputNodeClassName)

//=================================================
//Original node functions

//If you don't need to initialize node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, initializeNode)
{
	NOUNUSEDWARNING;
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
	return 1;
}

//If you don't need to manually close node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, closeNode)
{
	NOUNUSEDWARNING;
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
	return 1;
}

//=================================================
//Extended node functions ( RazorASCII )

//If you don't need to initialize node, you can delete this code segment
NODE_EXFUNC_DEF_EXPORT(bool, initializeNode, RazorASCII)
{
	NOUNUSEDWARNING;
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_EXFUNC_DEF_EXPORT(bool, openNode, RazorASCII)
{
	NOUNUSEDWARNING;
	return 1;
}

//If you don't need to manually close node, you can delete this code segment
NODE_EXFUNC_DEF_EXPORT(bool, closeNode, RazorASCII)
{
	NOUNUSEDWARNING;
	return 1;
}

//As an extended main function, if you delete this code segment, original main function will be used
NODE_EXFUNC_DEF_EXPORT(bool, main, RazorASCII)
{
	NOUNUSEDWARNING;
	return 1;
}


