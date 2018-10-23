from classifiers.classifier import Classifier
from preprocess.test_processor import TestProcessor
from time import ctime, sleep
from utils.result_accumulator import ResultAccumulator

if __name__ != '__main__':
    print("This module must be run as the main module.")
    exit(1)

# Reads the model first and creates a preprocessor.
classifier = Classifier("models/random_forest.pkl")

# Instantiates a result accumulator.
classes = ["chicken", "number7", "sidestep", "turnclap", "wipers", "stationary"]
accumulator = ResultAccumulator(classes, threshold=10)

# Creates a processor for input data.
x_columns = ["mean_handAcclX", "mean_handAcclY", "mean_handAcclZ",
             "mean_legAcclX", "mean_legAcclY", "mean_legAcclZ",
             "mean_BodyX", "mean_BodyY", "mean_BodyZ",
             "mean_legGyroX", "mean_legGyroY", "mean_legGyroZ",
             "mean_handGyroX", "mean_handGyroY", "mean_handGyroZ"]
processor = TestProcessor(x_columns)

while True:
    # Starts a new iteration with current time printed out.
    print("Enter a new iteration of capturing: ", ctime())

    # Predicts the output according to the input.
    input_data = processor.get_data()
    result = classifier.predict_once(input_data)
    print("The prediction result is", result)

    # Accumulates the result and sees whether it reaches the threshold.
    if accumulator.add(result):
        # Clears the accumulator.
        accumulator.clear()

        # Exits from the loop if this is the logout action.
        if result == "logout":
            break
        elif result == "stationary":
            print("Detected as stationary state")
        else:
            print("Going to send the result '%s' to remote server." % result)
            processor.send_result(result)

    # Sleeps for a certain period to wait for the next iteration to begin.
    sleep(0.2)

print("Thanks for using the DanceDance system!")
exit()
