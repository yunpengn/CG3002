from sklearn.externals import joblib
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
from preprocess.train_processor import TrainProcessor


# kNN naturally supports multi-class classification.
class KnnTrainer:
    def __init__(self, n_neighbors):
        self.classifier = KNeighborsClassifier(n_neighbors=n_neighbors)

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

    @staticmethod
    def find_best_knn_value(X, y):
        X_train, X_test, y_train, y_test = TrainProcessor.split(X, y)
        max_knn_value = 1
        max_score = 0

        for i in range(1, 10):
            classifier = KNeighborsClassifier(n_neighbors=i)
            classifier.fit(X_train, y_train)
            prediction_score = classifier.score(X_test, y_test)

            if prediction_score > max_score:
                max_knn_value = i
                max_score = prediction_score

        print("\nThe best value of k is:\n%s" % max_knn_value)
        print("\nThe max classification score is:\n%s" % max_score)
        return max_knn_value
