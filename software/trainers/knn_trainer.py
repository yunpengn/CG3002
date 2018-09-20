from sklearn.externals import joblib
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics

# kNN naturally supports multi-class classification.
class KnnTrainer:
	def __init__(self, n_neighbors):
		self.classifier = KNeighborsClassifier(n_neighbors = n_neighbors)

	def train(self, X, y):
		print("Going to train the model on a training dataset with size %d." % len(X))
		self.classifier.fit(X, y)
		print("We have got the following model: %s" % self.classifier)

	def evaluate(self, X, y):
		print("Going to evaluate the model on a training dataset with size %d." % len(X))
		predicted = self.classifier.predict(X)

		print("\nThe classification report for the classifier is:\n%s" % metrics.classification_report(y, predicted))
		print("The confusion matrix for the classifier is:\n%s" % metrics.confusion_matrix(y, predicted))

	def save(self, model_path):
		print("Going to save the model to persistence layer.")
		joblib.dump(self.classifier, model_path)
		print("Model successfully saved at %s" % model_path)

	def find_best_knn_value(self, X, y):
		max_knn_value = 1
		max_score = 0
		neighbors = np.arange(1,9)

		for i,x in enumerate(neighbors):
		    classifier = KNeighborsClassifier(n_neighbors=x)
		    classifier.fit(X, y)
		    prediction_score = classifier.predict(X_test)

		    if max_score < classifier.score(X_test, y_test):
		        max_knn_value = x
		        max_score = classifier.score(X_test, y_test)
		        max_prediction_score = prediction_score 

		print("\nThe best value of k is:\n%s" % max_knn_value)
		print("\nThe max classification score is:\n%s" % max_score)
		return max_knn_value
