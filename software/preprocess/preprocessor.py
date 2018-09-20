import numpy as np
import pandas as panda
from sklearn.model_selection import train_test_split

class Preprocessor:
	def __init__(self, X_columns, y_column):
		self.X_columns = X_columns
		self.y_column  = y_column

	def prepare_train(self, data_path, test_size = 0.2):
		# First read the data from CSV file format to panda dataframe format.
		dataset = panda.read_csv(data_path, sep = ',')

		# Then, only keep the relevant column
		data_X = dataset[self.X_columns].copy()
		data_y = dataset[self.y_column].copy()

		return train_test_split(data_X, data_y, test_size = 0.2, random_state = 0)

	def prepare_predict(self, data_path):
		# First read the data from CSV file format to panda dataframe format.
		dataset = panda.read_csv(data_path, sep = ',')
