from preprocess.raw_processor import RawProcessor


classes = ["chicken", "cowboy", "logout", "mermaid", "numbersix", "number7", "salute",
           "sidestep", "swing", "stationary", "turnclap", "wipers"]
x_columns = ["handAcclX", "handAcclY", "handAcclZ",
             "legAcclX", "legAcclY", "legAcclZ",
             "BodyX", "BodyY", "BodyZ",
             "legGyroX", "legGyroY", "legGyroZ",
             "handGyroX", "handGyroY", "handGyroZ"]
processor = RawProcessor(classes, x_columns)
processor.process("data/raw", "data/extract")
