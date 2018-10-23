from utils.data_client import DataClient


class TestProcessor:
    def __init__(self, x_columns):
        self.x_columns = x_columns
        self.data_client = DataClient()

    def get_data(self):
        input_data = self.data_client.getMlData()
        return [input_data[column_name] for column_name in self.x_columns]

    def send_result(self, prediction_output):
        return
