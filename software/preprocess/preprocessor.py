import numpy as np
import pandas as panda
from sklearn.model_selection import train_test_split

class Preprocessor:
	def __init__(self, X_columns, y_column):
		self.X_columns = X_columns
		self.y_column  = y_column

	def prepare(self, data_path, test_size = 0.2):
		dataset = panda.read_csv(data_path, sep = ',')
		data_X = dataset[self.X_columns].copy()
		data_y = dataset[self.y_column].copy()
		return train_test_split(data_X, data_y, test_size = 0.2, random_state = 0)
