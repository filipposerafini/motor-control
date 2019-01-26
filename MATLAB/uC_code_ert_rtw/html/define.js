function CodeDefine() { 
this.def = new Array();
this.def["IsrOverrun"] = {file: "ert_main_c.html",line:26,type:"var"};this.def["OverrunFlag"] = {file: "ert_main_c.html",line:27,type:"var"};this.def["rt_OneStep"] = {file: "ert_main_c.html",line:28,type:"fcn"};this.def["stopRequested"] = {file: "ert_main_c.html",line:45,type:"var"};this.def["main"] = {file: "ert_main_c.html",line:46,type:"fcn"};this.def["rtDW"] = {file: "uC_code_c.html",line:33,type:"var"};this.def["rtM_"] = {file: "uC_code_c.html",line:36,type:"var"};this.def["rtM"] = {file: "uC_code_c.html",line:37,type:"var"};this.def["rate_scheduler"] = {file: "uC_code_c.html",line:56,type:"fcn"};this.def["SystemCore_release_f2l"] = {file: "uC_code_c.html",line:68,type:"fcn"};this.def["SystemCore_delete_f2l"] = {file: "uC_code_c.html",line:75,type:"fcn"};this.def["matlabCodegenHandle_matlabC_f2l"] = {file: "uC_code_c.html",line:80,type:"fcn"};this.def["SystemCore_release"] = {file: "uC_code_c.html",line:88,type:"fcn"};this.def["SystemCore_delete"] = {file: "uC_code_c.html",line:96,type:"fcn"};this.def["matlabCodegenHandle_matlabCodeg"] = {file: "uC_code_c.html",line:101,type:"fcn"};this.def["SystemCore_release_f2"] = {file: "uC_code_c.html",line:109,type:"fcn"};this.def["SystemCore_delete_f2"] = {file: "uC_code_c.html",line:117,type:"fcn"};this.def["matlabCodegenHandle_matlabCo_f2"] = {file: "uC_code_c.html",line:122,type:"fcn"};this.def["uC_code_step"] = {file: "uC_code_c.html",line:131,type:"fcn"};this.def["uC_code_initialize"] = {file: "uC_code_c.html",line:296,type:"fcn"};this.def["RT_MODEL"] = {file: "uC_code_h.html",line:50,type:"type"};this.def["mbed_AnalogInput"] = {file: "uC_code_h.html",line:63,type:"type"};this.def["mbed_PWMOutput"] = {file: "uC_code_h.html",line:75,type:"type"};this.def["mbed_DigitalRead"] = {file: "uC_code_h.html",line:88,type:"type"};this.def["DW"] = {file: "uC_code_h.html",line:125,type:"type"};this.def["MWDSP_EPH_R_B"] = {file: "../../slprj/ert/_sharedutils/html/MWDSP_EPH_R_B_c.html",line:18,type:"fcn"};this.def["int8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:46,type:"type"};this.def["uint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:47,type:"type"};this.def["int16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:48,type:"type"};this.def["uint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:49,type:"type"};this.def["int32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:50,type:"type"};this.def["uint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:51,type:"type"};this.def["int64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:52,type:"type"};this.def["uint64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:53,type:"type"};this.def["real32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:54,type:"type"};this.def["real64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:55,type:"type"};this.def["real_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:61,type:"type"};this.def["time_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:62,type:"type"};this.def["boolean_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:63,type:"type"};this.def["int_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:64,type:"type"};this.def["uint_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:65,type:"type"};this.def["ulong_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:66,type:"type"};this.def["ulonglong_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:67,type:"type"};this.def["char_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:68,type:"type"};this.def["uchar_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:69,type:"type"};this.def["byte_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:70,type:"type"};this.def["pointer_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:91,type:"type"};}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["uC_code_c.html"] = "../uC_code.c";
	this.html2Root["uC_code_c.html"] = "uC_code_c.html";
	this.html2SrcPath["uC_code_h.html"] = "../uC_code.h";
	this.html2Root["uC_code_h.html"] = "uC_code_h.html";
	this.html2SrcPath["MWDSP_EPH_R_B_c.html"] = "../MWDSP_EPH_R_B.c";
	this.html2Root["MWDSP_EPH_R_B_c.html"] = "../../slprj/ert/_sharedutils/html/MWDSP_EPH_R_B_c.html";
	this.html2SrcPath["MWDSP_EPH_R_B_h.html"] = "../MWDSP_EPH_R_B.h";
	this.html2Root["MWDSP_EPH_R_B_h.html"] = "../../slprj/ert/_sharedutils/html/MWDSP_EPH_R_B_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "../../slprj/ert/_sharedutils/html/rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.html2SrcPath["MW_target_hardware_resources_h.html"] = "../MW_target_hardware_resources.h";
	this.html2Root["MW_target_hardware_resources_h.html"] = "MW_target_hardware_resources_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","uC_code_c.html","uC_code_h.html","MWDSP_EPH_R_B_c.html","MWDSP_EPH_R_B_h.html","rtwtypes_h.html","rtmodel_h.html","MW_target_hardware_resources_h.html"];
