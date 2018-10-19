from preprocess.train_test_processor import Preprocessor
from trainers.knn_trainer import KnnTrainer

x_columns = ["handAcclX", "handAcclY", "handAcclZ", "legAcclX", "legAcclY", "legAcclZ", "BodyX", "BodyY", "BodyZ"]
y_column = "label"
processor = Preprocessor(x_columns, y_column)

all_paths = ["chicken.csv", "number7.csv", "sidestep.csv", "turnclap.csv", "wipers.csv"]
x_train, x_test, y_train, y_test = processor.prepare_train_all("data/extract", all_paths)

trainer = KnnTrainer(5)
trainer.train(x_train, y_train)
trainer.evaluate(x_test, y_test)
