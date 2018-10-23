import pandas as panda


class TestProcessor:
    def __init__(self, x_columns, y_column):
        self.x_columns = x_columns
        self.y_column = y_column

    def prepare_predict(self, data_path):
        # First read the data from CSV file format to panda data-frame format.
        data_frame = panda.read_csv(data_path, sep=', ')
        # Gets the average of the columns we need.
        return np.array([data_frame[column].mean() for column in self.x_columns])