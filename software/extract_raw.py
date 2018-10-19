from preprocess.raw_processor import RawProcessor

# classes = ["chicken", "number7", "sidestep", "turnclap", "wipers"]
classes = ["chicken", "number7", "sidestep", "wipers"]
x_columns = ["handAcclX", "handAcclY", "handAcclZ", "legAcclX", "legAcclY", "legAcclZ", "BodyX", "BodyY", "BodyZ"]
processor = RawProcessor(classes, x_columns)
processor.process("data/raw", "data/extract")
