from preprocess.train_processor import TrainProcessor
from trainers.random_forest_trainer import RandomForestTrainer

x_columns = ["mean_handAcclX", "mean_handAcclY", "mean_handAcclZ",
             "mean_legAcclX", "mean_legAcclY", "mean_legAcclZ",
             "mean_BodyX", "mean_BodyY", "mean_BodyZ",
             "mean_legGyroX", "mean_legGyroY", "mean_legGyroZ",
             "mean_handGyroX", "mean_handGyroY", "mean_handGyroZ"]
y_column = "label"
processor = TrainProcessor(x_columns, y_column)

all_paths = ["chicken.csv", "cowboy.csv", "logout.csv", "mermaid.csv", "numbersix.csv", "number7.csv", "salute.csv",
             "sidestep.csv", "swing.csv", "stationary.csv", "turnclap.csv", "wipers.csv"]
x_train, x_test, y_train, y_test = processor.prepare_train_all("data/extract", all_paths)

trainer = RandomForestTrainer(14)
trainer.train(x_train, y_train)
trainer.evaluate(x_test, y_test)
trainer.save("models/random_forest.pkl")
