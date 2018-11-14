from classifiers.classifier import Classifier
from preprocess.test_processor import TestProcessor
from time import ctime, sleep
from sys import exit
from utils.result_accumulator import ResultAccumulator

if __name__ != '__main__':
    print("This module must be run as the main module.")
    exit(1)

# Reads the model first and creates a preprocessor.
classifier = Classifier("models/random_forest.pkl")

# Instantiates a result accumulator.
classes = {"chicken": 5, "number7": 11, "sidestep": 10, "turnclap": 4, "wipers": 5, "stationary": 5,
           "cowboy": 10, "mermaid": 13, "numbersix": 10, "salute": 10, "swing": 7, "logout": 14}
accumulator = ResultAccumulator(classes)

# Creates a processor for input data.
x_columns = ["mean_handAcclX", "mean_handAcclY", "mean_handAcclZ",
             "mean_legAcclX", "mean_legAcclY", "mean_legAcclZ",
             "mean_BodyX", "mean_BodyY", "mean_BodyZ",
             "mean_legGyroX", "mean_legGyroY", "mean_legGyroZ",
             "mean_handGyroX", "mean_handGyroY", "mean_handGyroZ"]

server_ip = "192.168.137.1"
server_port = 3002
server_aes_key = "0123456789abcdef"
processor = TestProcessor(x_columns, server_ip, server_port, server_aes_key)

# Sleeps to avoid the 1st-iteration bug.
initial_sleep_length = 57
for i in range(initial_sleep_length):
    print("Going to sleep for %s seconds." % (initial_sleep_length - i))
    sleep(1)

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
        accumulator.clear_all()

        # Exits from the loop if this is the logout action.
        if result == "logout":
            processor.send_result(result)
            break
        elif result == "stationary":
            print("Detected as stationary state")
        else:
            print("Going to send the result '%s' to remote server." % result)
            processor.send_result(result)

            # Sleeps 1 seconds to give response time for the dancer.
            sleep(1)

    # Sleeps for a certain period to wait for the next iteration to begin.
    sleep(0.2)

# Sleeps for a certain period before exit to be safe.
sleep(3)
print("Thanks for using the DanceDance system!")
exit()
