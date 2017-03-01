module dsp_subsystem (
	input sample_clock, reset,
	input [1:0] selector,
	input [15:0] input_sample,
	output [15:0] output_sample
	);

	assign output_sample = input_sample;

endmodule
