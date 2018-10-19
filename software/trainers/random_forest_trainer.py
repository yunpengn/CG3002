from sklearn.externals import joblib
from sklearn.ensemble import RandomForestClassifier
from sklearn import metrics


# Random forest
class RandomForestTrainer:
    def __init__(self, depth_max):
        self.classifier = RandomForestClassifier(n_estimators=100, max_depth=depth_max, random_state=0)

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
