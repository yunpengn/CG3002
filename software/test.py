from classifiers.classifier import Classifier
from preprocess.train_test_processor import Preprocessor
from trainers.svm_trainer import SvmTrainer
from trainers.knn_trainer import KnnTrainer
from trainers.ann_trainer import AnnTrainer
from trainers.perceptron_trainer import PerceptronTrainer

data_lookup_table = {

	'sample_kaggle': {
		'raw_data_path': 'data/run_or_walk.csv',
		'save_data_path': 'models/sample_kaggle.pkl',
		'X_Columns' : ['acceleration_x', 'acceleration_y', 'acceleration_z', 'wrist'],
		'Y_Columns' : 'activity'
	},
	'old_raw_sample': {
		'raw_data_path': 'data/raw/old_raw_sample.csv',
		'save_data_path': 'models/old_raw_sample.pkl',
		'X_Columns' : ['x', 'y', 'z'],
		'Y_Columns' : 'label'
	},
	'raw_dataset_12Oct': {
		'raw_data_path': 'data/raw/raw_dataset_12Oct.csv',
		'save_data_path': 'models/raw_dataset_12Oct_sample.pkl',
		'X_Columns' : ['BodyX', 'handAcclX', 'handAcclY', 'handAcclZ', 'legAcclY'],
		'Y_Columns' : 'move'
	},
	# Consists of moves - sidestep, wipers, turnclap
	'raw_dataset_12Oct_1a': {
		'raw_data_path': 'data/raw/raw_dataset_12Oct_1a.csv',
		'save_data_path': 'models/raw_dataset_12Oct_1a_sample.pkl',
		'X_Columns' : ['BodyX', 'BodyY', 'BodyZ', 'handAcclX', 'handAcclY', 'handAcclZ', 'legAcclX', 'legAcclY'],
		'Y_Columns' : 'move'
	},
	# Consists of moves - chicken, number7
	'raw_dataset_12Oct_1b': {
		'raw_data_path': 'data/raw/raw_dataset_12Oct_1b.csv',
		'save_data_path': 'models/raw_dataset_12Oct_1b_sample.pkl',
		'X_Columns' : ['BodyX', 'BodyY', 'BodyZ', 'handAcclX', 'handAcclY', 'handAcclZ', 'legAcclX', 'legAcclY'],
		'Y_Columns' : 'move'
	},
	'raw_dataset_19Oct_1a': {
		'raw_data_path': 'data/extract/extracted_1.csv',
		'save_data_path': 'models/extracted_1.pkl',
		'X_Columns' : ['max_BodyX' , 'max_BodyY', 'max_BodyZ', 
						'max_handAcclX' , 'max_handAcclY' , 'max_handAcclZ',
						'max_legAcclX' , 'max_legAcclY' , 'max_legAcclZ', 
						'mean_BodyX', 'mean_BodyY' , 'mean_BodyZ',
						'mean_handAcclX', 'mean_handAcclY', 'mean_handAcclZ',
						'mean_legAcclX', 'mean_legAcclY', 'mean_legAcclZ' , 
						'min_BodyX' , 'min_BodyY', 'min_BodyZ' , 
						'min_handAcclX', 'min_handAcclY' , 'min_handAcclZ',
						'min_legAcclX', 'min_legAcclY' , 'min_legAcclZ',
						'std_BodyX', 'std_BodyY', 'std_BodyZ' ,
						'std_handAcclX', 'std_handAcclY', 'std_handAcclZ',
						'std_legAcclX','std_legAcclY','std_legAcclZ'],
		'Y_Columns' : 'label'
	}

}

########################################
# Initialise dataset to use
########################################

dataset = data_lookup_table['raw_dataset_19Oct_1a']

########################################
# Test for SVM
########################################

preprocessor = Preprocessor(dataset['X_Columns'], dataset['Y_Columns'])
X_train, X_test, y_train, y_test = preprocessor.prepare_train(dataset['raw_data_path'])
trainer = SvmTrainer()

trainer.train(X_train, y_train)
trainer.evaluate(X_test, y_test)
trainer.save(dataset['save_data_path'])
classifier = Classifier(dataset['save_data_path'])
prediction_score = classifier.predict(X_test)

print(prediction_score)

########################################
# Test for KNN
########################################

preprocessor = Preprocessor(dataset['X_Columns'], dataset['Y_Columns'])

X_train, X_test, y_train, y_test = preprocessor.prepare_train(dataset['raw_data_path'])
max_knn_value = KnnTrainer.find_best_knn_value(X_train, y_train)
trainer = KnnTrainer(max_knn_value)
trainer.train(X_train, y_train)
trainer.evaluate(X_test, y_test)
trainer.save(dataset['save_data_path'])
classifier = Classifier(dataset['save_data_path'])
prediction_score = classifier.predict(X_test)

print(prediction_score)

########################################
# Test for ANN
########################################

preprocessor = Preprocessor(dataset['X_Columns'], dataset['Y_Columns'])

X_train, X_test, y_train, y_test = preprocessor.prepare_train(dataset['raw_data_path'])
trainer = AnnTrainer(0.001)
trainer.train(X_train, y_train)
trainer.evaluate(X_test, y_test)
trainer.save(dataset['save_data_path'])
classifier = Classifier(dataset['save_data_path'])
prediction_score = classifier.predict(X_test)

print(prediction_score)

########################################
# Test for Perceptron Trainer
########################################

preprocessor = Preprocessor(dataset['X_Columns'], dataset['Y_Columns'])

X_train, X_test, y_train, y_test = preprocessor.prepare_train(dataset['raw_data_path'])
trainer = PerceptronTrainer(10000)
trainer.train(X_train, y_train)
trainer.evaluate(X_test, y_test)
trainer.save(dataset['save_data_path'])
classifier = Classifier(dataset['save_data_path'])
prediction_score = classifier.predict(X_test)

print(prediction_score)
