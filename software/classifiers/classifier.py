from sklearn.externals import joblib

class Classifier:
	def __init__(self, model_path):
		print("Attempting to load the model from %s" % model_path)
		self.model = joblib.load(model_path)
		print("Successfully loaded the model %s" % self.model)

	def predict(input):
		return model.predict(input)
