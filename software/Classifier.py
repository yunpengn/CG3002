from sklearn.externals import joblib

class Classifier:
	# The model we retrieved from the persistence layer.
	model

	def __init__(self, model_path):
		self.model = joblib.load(model_path)
