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

		return split(data_X, data_y, test_size = 0.2)

	def split(data_X, data_y, test_size = 0.2):
		return train_test_split(data_X, data_y, test_size = 0.2, random_state = 0)

	def prepare_predict(self, data_path):
		# First read the data from CSV file format to panda dataframe format.
		dataset = panda.read_csv(data_path, sep = ', ')
		# Gets the average of the columns we need.
		return np.array([dataset[column].mean() for column in self.X_columns])

	# We assume the raw data to be 100Hz.
	def read_raw(self, data_path, X_columns, interval = 20, period = 50):
		# First read the data from CSV file format to panda dataframe format.
		dataset = panda.read_csv(data_path, sep = ',')

		# Use a dict to store the input.
		X = {}
		# Use a dict to store the output (label).
		y = {}

		for column in X_columns:
			X['mean_' + column] = []
			X['std_' + column] = []
			X['min_' + column] = []
			X['max_' + column] = []

		y[self.y_column] = []

		# Process for every interval using overlapping frame technique
		for start in range(0, len(dataset) - period, interval):
			instance = {}

			# Process the data for each column
			for column in X_columns:
				current = dataset[column][start:start + period]
				X['mean_' + column].append(current.mean())
				X['std_' + column].append(current.std())
				X['min_' + column].append(current.min())
				X['max_' + column].append(current.max())

			y[self.y_column].append(dataset[self.y_column][start])

		return panda.DataFrame(data = X), panda.DataFrame(data = y)
