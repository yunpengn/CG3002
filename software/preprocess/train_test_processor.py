import numpy as np
import pandas as panda
from sklearn.model_selection import train_test_split


class Preprocessor:
    def __init__(self, x_columns, y_column):
        self.x_columns = x_columns
        self.y_column = y_column

    def prepare_train(self, data_path):
        data_x, data_y = self.extract_columns(data_path)
        return Preprocessor.split(data_x, data_y)

    def prepare_train_all(self, all_paths):
        result_x = panda.DataFrame(columns=self.x_columns)
        result_y = panda.DataFrame(columns=[self.y_column])

        for path in all_paths:
            data_x, data_y = self.extract_columns(path)
            result_x = result_x.append(data_x, ignore_index=True)
            result_y = result_y.append(data_y, ignore_index=True)

        return Preprocessor.split(result_x, result_y)

    def extract_columns(self, data_path, separator=","):
        # First read the data from CSV file format to panda data-frame format.
        data_frame = panda.read_csv(data_path, sep=separator)

        # Then, only keep the relevant column
        data_x = data_frame[self.x_columns].copy()
        data_y = data_frame[self.y_column].copy()

        return data_x, data_y

    @staticmethod
    def split(data_x, data_y, test_percent=0.2, random=0):
        return train_test_split(data_x, data_y, test_size=test_percent, random_state=random)

    def prepare_predict(self, data_path):
        # First read the data from CSV file format to panda data-frame format.
        data_frame = panda.read_csv(data_path, sep=', ')
        # Gets the average of the columns we need.
        return np.array([data_frame[column].mean() for column in self.x_columns])
