from classifiers.classifier import Classifier
from time import time, sleep
from utils.result_accumulator import ResultAccumulator

# Reads the model first and creates a preprocessor and an accumulator.
accumulator = ResultAccumulator(range(11))
classifier = Classifier("../models/sample_kaggle.pkl")
preprocessor = Preprocessor(['BodyX', 'handAcclX', 'handAcclY', 'handAcclZ', 'legAcclY'], 'Voltage')

while True:
	# Starts a new iteration with current time printed out.
	print("Enter a new iteration of capturing: ", time.time())

	# Predicts the output according to the input.
	input = preprocessor.prepare_predict('data/stationary_sample.csv')
	result = classifier.predict(input)
	print("The prediction result is", result)

	# Accumulates the result and sees whether it reaches the threshold.
	if accumulator.add(result):
		# [TODO] Send the result to the remove server

		# Clears the accumulator.
		accumulator.clear()

		# Exits from the loop if this is the logout action.
		if result == 10:
			break

	# Sleeps for a certain period to wait for the next iteration to begin.
	time.sleep(0.1)

print("Thanks for using the DanceDance system!")
exit()
