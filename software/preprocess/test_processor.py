from utils.data_client import DataClient


class TestProcessor:
    def __init__(self, x_columns):
        self.x_columns = set(x_columns)
        self.data_client = DataClient()

    def get_data(self):
        input_data = self.data_client.getMlData()
        return {key: value for key, value in input_data.items() if key in self.x_columns}

    def send_result(self, prediction_output):
        return
