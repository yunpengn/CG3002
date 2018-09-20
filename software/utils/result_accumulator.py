class ResultAccumulator:
	def __init__(self, outputs, threshold = 10):
		self.counter = { key:0 for key in outputs }
		self.outputs = outputs
		self.threshold = threshold

	def add(self, type):
		self.counter[type] += 1
		return self.counter[type] >= threshold

	def clear(self):
		self.counter = { key:0 for key in outputs }
