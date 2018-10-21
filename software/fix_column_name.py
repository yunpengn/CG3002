########################################################################
# WARNING: this is a custom script, for archived purposes only.
# We used this to fix the wrong column name in raw csv files.
# Don't run it unless you are absolutely sure what you are doing.
########################################################################
import os
from preprocess.raw_processor import RawProcessor
import shutil

classes = ["chicken", "number7", "sidestep", "turnclap", "wipers"]
prefix = "data/raw"

new_first_line = "Time, Energy, Voltage, Current, BodyX, BodyY, BodyZ, handAcclX, handAcclY, handAcclZ, " \
                 "handGyroX, handGyroY, handGyroZ, legAcclX, legAcclY, legAcclZ, legGyroX, legGyroY, legGyroZ\n"

all_paths = []
for class_name in classes:
    folder_path = os.path.join(prefix, class_name)
    all_paths += RawProcessor.get_file_names_in_folder(folder_path, extension="csv")
print("We will process the following files: %s" % all_paths)

for path in all_paths:
    file = open(path, mode="r+")
    file.read()
    file.seek(0, 0)
    file.write(new_first_line)
    file.close()
    print("Replaced the first line of %s" % path)
