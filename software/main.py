from trainers.svm_trainer import SvmTrainer

trainer = SvmTrainer('data/run_or_walk.csv')
trainer.prepare(['acceleration_x', 'acceleration_y', 'acceleration_z', 'wrist'], 'activity')
trainer.train()
trainer.evaluate()
trainer.save('models/sample_kaggle.pkl')
