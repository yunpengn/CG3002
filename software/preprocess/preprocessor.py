import numpy as np
import pandas as panda
from sklearn.model_selection import train_test_split


class Preprocessor:
    def __init__(self, x_columns, y_column):
        self.x_columns = x_columns
        self.y_column = y_column

    def prepare_train(self, data_path):
        # First read the data from CSV file format to panda data-frame format.
        data_frame = panda.read_csv(data_path, sep=', ')

        # Then, only keep the relevant column
        data_x = data_frame[self.x_columns].copy()
        data_y = data_frame[self.y_column].copy()

        return Preprocessor.split(data_x, data_y)

    @staticmethod
    def split(data_x, data_y, test_percent=0.2, random=0):
        return train_test_split(data_x, data_y, test_size=test_percent, random_state=random)

    def prepare_predict(self, data_path):
        # First read the data from CSV file format to panda data-frame format.
        dataset = panda.read_csv(data_path, sep=', ')
        # Gets the average of the columns we need.
        return np.array([dataset[column].mean() for column in self.x_columns])
