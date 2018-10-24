import os
import pandas as panda
import sys
import traceback

Y_COLUMN_NAME = "label"


class RawProcessor:
    def __init__(self, classes, x_columns):
        self.classes = classes
        self.x_columns = x_columns

    def process(self, origin_folder, dest_folder):
        for class_name in self.classes:
            # Gets the origin & destination folder for this specific class.
            origin_class_folder = os.path.join(origin_folder, class_name)

            # Creates a list of dictionaries, each of which will be a row of the output data-frame.
            rows = []

            # Extracts features & labels and concatenates everything together.
            for file_name in RawProcessor.get_file_names_in_folder(origin_class_folder, extension="csv"):
                rows += self.extract_features(file_name, class_name)

            # Creates a result data_frame
            data_frame = panda.DataFrame(rows)
            print("Stored the processing result (%d rows) of class %s to a data-frame." % (len(rows), class_name))

            # Stores the result to the extracted CSV file.
            output_name = os.path.join(dest_folder, class_name + ".csv")
            RawProcessor.save_csv(data_frame, output_name)
            print("Stored the processing result of class %s to file at %s." % (class_name, output_name))

        print("Finished the processing of all raw data files.")

    def extract_features(self, file_path, class_name, interval=20, period=100):
        # Reads a CSV file from the given path and converts the data into pandas data-frame format.
        data_frame = RawProcessor.read_csv(file_path, separator=", ")
        num_of_rows = data_frame.shape[0]
        print("Begin to handle the data-frame (%d rows) read from %s" % (num_of_rows, file_path))

        # Creates a list of dictionaries, each of which will be a row of the output data-frame.
        rows = []

        # Process for every interval using overlapping frame technique
        for start in range(0, num_of_rows - period, interval):
            instance = {}

            # Adds all extracted features.
            for column_name in self.x_columns:
                try:
                    current = data_frame[column_name][start:start + period]
                    instance['mean_' + column_name] = current.mean()
                    instance['var_' + column_name] = current.var()
                    instance['min_' + column_name] = current.min()
                    instance['max_' + column_name] = current.max()
                except:
                    print("When trying to extract %s from the rows (%d:%d):" % (column_name, start, start + period))
                    _, _, tb = sys.exc_info()
                    traceback.print_tb(tb)

            # Adds the label.
            instance[Y_COLUMN_NAME] = class_name

            # Appends this row to the list
            rows.append(instance)

        return rows

    def get_output_columns(self):
        columns = [Y_COLUMN_NAME]
        for x_name in self.x_columns:
            columns.append('mean_' + x_name)
            columns.append('var_' + x_name)
            columns.append('min_' + x_name)
            columns.append('max_' + x_name)

        return columns

    @staticmethod
    def get_file_names_in_folder(folder_path, extension=""):
        file_names = []
        for name in os.listdir(folder_path):
            full_name = os.path.join(folder_path, name)
            if os.path.isfile(full_name) and name.lower().endswith("." + extension):
                file_names.append(full_name)

        return file_names

    @staticmethod
    def read_csv(file_path, separator=','):
        return panda.read_csv(file_path, separator)

    @staticmethod
    def save_csv(data_frame, file_path, separator=',', encoding='utf-8', float_format='%.7f'):
        data_frame.to_csv(file_path, separator, encoding, float_format)
