from preprocess.train_test_processor import Preprocessor
from trainers.random_forest_trainer import RandomForestTrainer

x_columns = ["mean_handAcclX", "mean_handAcclY", "mean_handAcclZ", "mean_legAcclX", "mean_legAcclY", "mean_legAcclZ"]
y_column = "label"
processor = Preprocessor(x_columns, y_column)

# all_paths = ["chicken.csv", "number7.csv", "sidestep.csv", "turnclap.csv", "wipers.csv"]
all_paths = ["chicken.csv", "number7.csv", "sidestep.csv", "wipers.csv"]
x_train, x_test, y_train, y_test = processor.prepare_train_all("data/extract", all_paths)

trainer = RandomForestTrainer(3)
trainer.train(x_train, y_train)
trainer.evaluate(x_test, y_test)
