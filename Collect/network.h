int sgn(float net) {
	if (net > 0) {
		return 1;
	}
	else {
		return -1;
	}
}

float desired(float a) {
	if (a == 1) {
		return -1;
	}
	else {
		return 1;
	}
}

void train_pct(float* Samples, int numSample, float* targets, float* Weights, float* bias, int inputDim) {
	double lrn_const = 0.5;
	float total_err, err, net, output;
	bool tamam = true;
	while (tamam) {
		total_err = 0;
		for (int k = 0; k < numSample; k++) {
			net = 0;
			for (int i = 0; i < inputDim; i++) {
				net += Weights[i] * Samples[k * inputDim + i];
			}
			net += bias[0];
			output = sgn(net);
			err = (desired(targets[k])) - output;

			for (int i = 0; i < inputDim; i++) {
				Weights[i] += lrn_const * err * Samples[k * inputDim + i];
			}
			bias[0] += lrn_const * err;
			total_err += abs(err);
		}
		if (total_err == 0) {
			tamam = false;
		}
	}
}
