import numpy as np
import pandas as panda

from sklearn.externals import joblib
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn import metrics

class Trainer:
	def __init__(self, data_path):
		self.dataset = panda.read_csv(data_path, sep = ',')
		self.classifier = SVC()

	def prepare(self, X_columns, y_column, test_size = 0.2):
		data_X = self.dataset[X_columns].copy()
		data_y = self.dataset[y_column].copy()
		self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(data_X, data_y,
																				test_size = 0.2, random_state = 0)

	def train(self):
		print("Going to train the model on a training dataset with size %d." % len(self.X_train))
		self.classifier.fit(self.X_train, self.y_train)
		print("We have got the following model: %s" % self.classifier)

	def evaluate(self):
		expected = self.y_test
		predicted = self.classifier.predict(self.X_test)

		print("\nThe classification report for the classifier is:\n%s" % metrics.classification_report(expected, predicted))
		print("The confusion matrix for the classifier is:\n%s" % metrics.confusion_matrix(expected, predicted))

	def save(self, model_path):
		print("Going to save the model to persistence layer.")
		joblib.dump(self.classifier, model_path)
		print("Model successfully saved at %s" % model_path)

trainer = Trainer('../data/run_or_walk.csv')
trainer.prepare(['acceleration_x', 'acceleration_y', 'acceleration_z', 'wrist'], 'activity')
trainer.train()
trainer.evaluate()
trainer.save('../models/sample_kaggle.pkl')
