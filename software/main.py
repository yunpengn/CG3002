from classifiers.classifier import Classifier
from trainers.svm_trainer import SvmTrainer
from preprocess.preprocessor import Preprocessor

preprocessor = Preprocessor(['acceleration_x', 'acceleration_y', 'acceleration_z', 'wrist'], 'activity')
X_train, X_test, y_train, y_test = preprocessor.prepare('data/run_or_walk.csv')

trainer = SvmTrainer()
trainer.train(X_train, y_train)
trainer.evaluate(X_test, y_test)
trainer.save('models/sample_kaggle.pkl')

classifier = Classifier("../models/sample_kaggle.pkl")
