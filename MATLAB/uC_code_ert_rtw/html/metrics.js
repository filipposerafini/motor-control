function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["MWDSP_EPH_R_B"] = {file: "E:\\Università\\Magistrale - Advanced Automotive Electronic Engineering\\Compliance Design of Automotive Systems\\motor-control\\MATLAB\\slprj\\ert\\_sharedutils\\MWDSP_EPH_R_B.c",
	stack: 24,
	stackTotal: 24};
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
	 this.codeMetricsSummary = '<a href="uC_code_metrics.html">Global Memory: 0(bytes) Maximum Stack: 24(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
