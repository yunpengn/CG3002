from utils.client_data import DataClient
from utils.client_result import ResultClient


class TestProcessor:
    def __init__(self, x_columns, server_ip, server_port, aes_key):
        if len(aes_key) != 8 and len(aes_key) != 16 and len(aes_key) != 24:
            raise ValueError("The AES key provided is of invalid length.")
        self.x_columns = x_columns
        self.data_client = DataClient()
        self.result_client = ResultClient(server_ip, server_port, aes_key)

    def get_data(self):
        input_data = self.data_client.getMlData()
        return [input_data[column_name] for column_name in self.x_columns]

    def send_result(self, prediction_output):
        power_data = self.data_client.getPowerData()
        self.result_client.sendData(prediction_output, str(power_data["voltage"]), str(power_data["current"]),
                                    str(power_data["power"]), str(power_data["cumpower"]))
