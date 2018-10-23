from classifiers.classifier import Classifier
from preprocess.test_processor import TestProcessor
from time import time, sleep
from utils.result_accumulator import ResultAccumulator

if __name__ != '__main__':
    print("This module must be run as the main module.")
    exit(1)

# Reads the model first and creates a preprocessor.
classifier = Classifier("models/random_forest.pkl")

# Instantiates a result accumulator.
accumulator = ResultAccumulator(range(12))

# Creates a processor for input data.
x_columns = ["mean_handAcclX", "mean_handAcclY", "mean_handAcclZ",
             "mean_legAcclX", "mean_legAcclY", "mean_legAcclZ",
             "mean_BodyX", "mean_BodyY", "mean_BodyZ",
             "mean_legGyroX", "mean_legGyroY", "mean_legGyroZ",
             "mean_handGyroX", "mean_handGyroY", "mean_handGyroZ"]
y_column = "label"
processor = TestProcessor(x_columns, y_column)

while True:
    # Starts a new iteration with current time printed out.
    print("Enter a new iteration of capturing: ", time())

    # Predicts the output according to the input.
    input = processor.prepare_predict("data/stationary_sample.csv")
    result = classifier.predict(input)
    print("The prediction result is", result)

    # Accumulates the result and sees whether it reaches the threshold.
    if accumulator.add(result):
        # Clears the accumulator.
        accumulator.clear()

        # Exits from the loop if this is the logout action.
        if result == 11:
            break
        elif result == 10:
            print("Detected as stationary state")
        else:
            print("Going to send result to remote server.")
            # [TODO] Send the result to the remove server

    # Sleeps for a certain period to wait for the next iteration to begin.
    sleep(0.1)

print("Thanks for using the DanceDance system!")
exit()
