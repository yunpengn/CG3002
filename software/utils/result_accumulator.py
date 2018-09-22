class ResultAccumulator:
    def __init__(self, outputs, threshold=10):
        self.counter = {key: 0 for key in outputs}
        self.outputs = outputs
        self.threshold = threshold

    def add(self, label):
        self.counter[label] += 1
        return self.counter[label] >= self.threshold

    def clear(self):
        self.counter = {key: 0 for key in self.outputs}
