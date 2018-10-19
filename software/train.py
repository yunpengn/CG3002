from preprocess.train_test_processor import Preprocessor

x_columns = ["handAcclX", "handAcclY", "handAcclZ", "legAcclX", "legAcclY", "legAcclZ", "BodyX", "BodyY", "BodyZ"]
y_column = "label"
processor = Preprocessor(x_columns, y_column)
processor.