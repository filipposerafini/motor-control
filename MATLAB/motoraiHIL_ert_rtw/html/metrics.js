function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtInf"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtInfF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.var["rtMinusInf"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtMinusInfF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.var["rtNaN"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 8};
	 this.metricsArray.var["rtNaNF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	size: 4};
	 this.metricsArray.fcn["MWDSP_EPH_R_B"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\MWDSP_EPH_R_B.c",
	stack: 24,
	stackTotal: 24};
	 this.metricsArray.fcn["fabs"] = {file: "C:\\Program Files\\MATLAB\\R2018b\\sys\\lcc\\include\\math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["floor"] = {file: "C:\\Program Files\\MATLAB\\R2018b\\sys\\lcc\\include\\math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["inv_6TJweJmr"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\inv_6TJweJmr.c",
	stack: 16,
	stackTotal: 16};
	 this.metricsArray.fcn["inv_t6RrLIHb"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\inv_t6RrLIHb.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["pow"] = {file: "C:\\Program Files\\MATLAB\\R2018b\\sys\\lcc\\include\\math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtGetInf"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 20,
	stackTotal: 20};
	 this.metricsArray.fcn["rtGetInfF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rtGetMinusInf"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 20,
	stackTotal: 20};
	 this.metricsArray.fcn["rtGetMinusInfF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rtGetInf.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rtGetNaN"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rtGetNaN.c",
	stack: 20,
	stackTotal: 20};
	 this.metricsArray.fcn["rtGetNaNF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rtGetNaN.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rtIsInf"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtIsInfF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtIsNaN"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 13,
	stackTotal: 13};
	 this.metricsArray.fcn["rtIsNaNF"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["rt_InitInfAndNaN"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_nonfinite.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rt_powd_snf"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\rt_powd_snf.c",
	stack: 24,
	stackTotal: 24};
	 this.metricsArray.fcn["sqrt"] = {file: "C:\\Program Files\\MATLAB\\R2018b\\sys\\lcc\\include\\math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["xnrm2_ooZ215qV"] = {file: "C:\\Users\\Filippo\\Documents\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\xnrm2_ooZ215qV.c",
	stack: 40,
	stackTotal: 40};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="motoraiHIL_metrics.html">Global Memory: 36(bytes) Maximum Stack: 40(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
