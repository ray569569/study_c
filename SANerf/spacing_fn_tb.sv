`timescale 1ns / 10ps
module spacing_fn_TB(
	clk,
	rst_n,
    i_valid,
	i_data,
	o_valid,
	o_data
);

output logic  clk, rst_n, i_valid;
output logic [20:0] i_data_1,i_data_2,i_data_3,i_data_4;

input o_valid; 
input [12:0] o_data_1,o_data_2,o_data_3,o_data_4; 

integer i, j, k, seed, latency;
integer input_file,temp;
integer golden_file;

logic signed [12:0] golden[0:3];
logic signed [12:0] ans[0:3];
logic [20:0] i_data[0:3];

parameter   cycle = 40,
            stop_cycle = 1000,
			tolerant = 1;

spacing_fn DUT(clk,
	rst_n,
    i_valid,
	i_data_1,
	i_data_2,
	i_data_3,
	i_data_4,
	o_valid,
	o_data_1,
	o_data_2,
	o_data_3,
	o_data_4
);
//initialize and generate the clk signal 
initial clk = 0;
always #(cycle/2.0) clk = ~clk;

//dump the fsdb waveform file
`ifdef RTL
initial begin
    $fsdbDumpfile("spacing_fn.fsdb");
    $fsdbDumpvars;
	$fsdbDumpMDA ;
end
`elsif GATE 
initial begin
    $fsdbDumpfile("spacing_fn_GATE.fsdb");
    $fsdbDumpvars(0, DUT, "+mda");
    $sdf_annotate("../02_SYN/Netlist/spacing_fn_SYN.sdf", DUT);
end
/*
`elsif POST
initial begin
//    $fsdbDumpfile("IM_POST.fsdb");
//    $fsdbDumpvars();
    $dumpfile("IM_POST.vcd");
    $dumpvars(0, DUT);
    $sdf_annotate("../04_APR/IM_POST.sdf", DUT);
end
*/
`endif
//(golden[k]*tolerant)/100)
task check_ans ; begin
	for(k=0;k<4;k = k+1) begin
		if(!((golden[k] - ans[k] <=12) && (golden[k] - ans[k] >= -12))) begin
			$display ("--------------------------------------------------------------------------------------------------------------------------------------------");
			$display ("                                                                    SPEC 1 FAIL                                                             ");
			$display ("                                                                    YOUR:  %d                                                        ",ans[k]);
			$display ("                                                                    GOLDEN: %d                                                    ",golden[k]);
			$display ("--------------------------------------------------------------------------------------------------------------------------------------------");
			$finish ;
		end
	end
end endtask


// wait out valid task
task wait_out_valid_task; begin
	latency = 0;
	// wait out valid
	while(o_valid === 0) begin
		@ (negedge clk);
		latency = latency + 1;
	end
end endtask

initial begin
    rst_n = 1;
    i_valid = 1'b0;

	
	input_file = $fopen("../00_TEST/pattern.txt","r");
	golden_file = $fopen("../00_TEST/golden.txt","r");
	
    @(negedge clk);
    @(negedge clk); rst_n = 0;
    @(negedge clk); rst_n = 1;
    @(negedge clk);
	
	i_valid = 1'b1;
    for(i=0;i<250;i=i+1) begin 
        // input task
		for(j=0;j<4;j=j+1) begin
			temp = $fscanf(input_file, "%d", i_data[j]);
		end
		i_data_1 = i_data[0];
		i_data_2 = i_data[1];
		i_data_3 = i_data[2];
		i_data_4 = i_data[3];
		
		
		
        // end of input task
		//wait_out_valid_task();
		if(o_valid) begin
			for(j=0;j<4;j=j+1) begin
				temp = $fscanf(golden_file, "%d", golden[j]);
			end
			ans[0] = o_data_1;
			ans[1] = o_data_2;
			ans[2] = o_data_3;
			ans[3] = o_data_4;
			check_ans();
			$display("Pattern %3d Pass Latency = %3d Cycles", i+1, latency);
        end
        
        @(negedge clk);
    end
	i_valid = 1'b0;
    
    YOU_PASS_task();

    $display("\n---Simulation End---\n");
    $finish;
end

task YOU_PASS_task;begin

$display ("--------------------------------------------------------------------------------------------------------------------------------------------");
$display ("                                                               Congratulations!                						             ");
$display ("                                                        You have passed all patterns!          						             ");
$display ("                                                                Time: %0t ns                                                         ",$time/1000.0);
$display ("--------------------------------------------------------------------------------------------------------------------------------------------");
$finish;	
end endtask


endmodule

