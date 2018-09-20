from classifiers.classifier import Classifier
from preprocess.preprocessor import Preprocessor
from trainers.svm_trainer import SvmTrainer
from trainers.knn_trainer import KnnTrainer

########################################
# Test for run or walk
########################################

preprocessor = Preprocessor(['acceleration_x', 'acceleration_y', 'acceleration_z', 'wrist'], 'activity')
X_train, X_test, y_train, y_test = preprocessor.prepare_train('data/run_or_walk.csv')

trainer = SvmTrainer()
trainer.train(X_train, y_train)
trainer.evaluate(X_test, y_test)
trainer.save('models/sample_kaggle.pkl')

classifier = Classifier("../models/sample_kaggle.pkl")

########################################
# Test for stationary sample data
########################################

preprocessor = Preprocessor(['BodyX', 'handAcclX', 'handAcclY', 'handAcclZ', 'legAcclY'], 'Voltage')
input = preprocessor.prepare_predict('data/stationary_sample.csv')
print(input)

########################################
# Test for raw movement dataset
########################################

preprocessor = Preprocessor(['x1', 'y1', 'z1', 'x2', 'y2', 'z2', 'x3', 'y3', 'z3'], 'class')
input = preprocessor.prepare_predict('data/raw_movement_dataset.csv')

trainer = KnnTrainer()
#Note: Can choose to call this inside the class itself
knn_value = trainer.find_best_knn_value()
trainer.train(X_train, y_train, knn_value)
trainer.evaluate(X_test, y_test)