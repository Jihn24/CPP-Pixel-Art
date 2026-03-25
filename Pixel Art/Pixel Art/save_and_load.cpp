int save_index = 0;
string new_save_name;
bool input_menu_open = true;
const char* save;
DWORD bytes_written;
u32 save_data_int;
string save_data_string;
const char* save_data_char;
DWORD file_exists;
bool save_all;

internal void
SetSaveAll(bool full_page) {
	save_all = full_page;
}
internal bool
GetSaveAll() {
	return save_all;
}

internal void
SaveMatrix(string save_name) {	
	save = save_name.c_str();

	HANDLE write_save_file = CreateFile(save, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	string size = to_string(GetMatrixWidth()) + "x" + to_string(GetMatrixHeight()) + "s";
	const char* save_size = size.c_str();
	WriteFile(write_save_file, save_size, strlen(save_size), &bytes_written, NULL);

	for (int i = 0; i < GetMatrixWidth(); i++) {
		for (int j = 0; j < GetMatrixHeight(); j++) {
			save_data_int = GetMatrix(i, j);
			save_data_string = DecToHex(save_data_int);
			if (save_data_string.size() == 5) {
				save_data_string = "0" + save_data_string;
			}
			else if (save_data_string.size() == 4) {
				save_data_string = "00" + save_data_string;
			}
			save_data_char = save_data_string.c_str();

			WriteFile(write_save_file, save_data_char, strlen(save_data_char), &bytes_written, NULL);			
		}
	}

	CloseHandle(write_save_file);
}

string next_colour;

internal string
GetNextColour() {
	next_colour = "";

	for (int i = 0; i < 6; i++) {
		string data = GetColourData();
		next_colour += data[0];
		RemoveData(0, 1);
	}

	return next_colour;
}

DWORD bytes_read;
BYTE buffer[10];
const char* load;
string width;
string height;
u32 save_width;
u32 save_height;
bool getting_width;
bool getting_height;
u32 file_size_length;
u32 buffer_length;
BYTE* new_buffer;

internal void
LoadMatrix(string save_name) {
	load = save_name.c_str();
	file_exists = GetFileAttributes(load);
	if (file_exists != 0xffffffff) {
		bytes_read;
		buffer[10];

		HANDLE read_save_file_length = CreateFile(load, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(read_save_file_length, buffer, sizeof(buffer), &bytes_read, NULL);

		SetColourData((char*)buffer);

		width = "";
		height = "";
		getting_width = true;
		getting_height = true;

		while (getting_width) {
			string data_with_size = GetColourData();
			char next_letter = data_with_size[0];
			if (next_letter == 'x') {
				RemoveData(0, 1);
				getting_width = true;
				break;
			}
			width += data_with_size[0];
			RemoveData(0, 1);
		}

		while (getting_height) {
			string data_with_size = GetColourData();
			char next_letter = data_with_size[0];
			if (next_letter == 's') {
				RemoveData(0, 1);
				getting_height = true;
				break;
			}
			height += data_with_size[0];
			RemoveData(0, 1);
		}

		CloseHandle(read_save_file_length);		

		save_width = stoi(width);
		save_height = stoi(height);

		if (save_name != "..\\resize_temp_file.txt") {
			SetMatrixSize(save_width, save_height);
		}

		file_size_length = width.length() + height.length() + 2;
		buffer_length = file_size_length + (6 * save_width * save_height);

		new_buffer = new BYTE[buffer_length];

		HANDLE read_save_file = CreateFile(load, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		long file_size = GetFileSize(read_save_file, NULL);
		ReadFile(read_save_file, new_buffer, file_size, &bytes_read, NULL);

		SetColourData((char*)new_buffer);
		RemoveData(0, file_size_length);

		string load_colour_string;

		for (u32 i = 0; i < save_width; i++) {
			for (u32 j = 0; j < save_height; j++) {
				load_colour_string = "0x" + GetNextColour();
				u32 load_colour_hex = stoi(load_colour_string, 0, 16);
				if (save_name != "..\\resize_temp_file.txt")
					SetMatrix(i, j, load_colour_hex, 1, 1);
				else if ( i < GetMatrixWidth() && j < GetMatrixHeight())
					SetMatrix(i, j, load_colour_hex, 1, 1);
			}
		}

		CloseHandle(read_save_file);
	}	
}

internal void
SaveSelectedArea(string save_name) {
	save = save_name.c_str();

	HANDLE write_save_file = CreateFile(save, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	string size = to_string(GetSelectedAreaWidth()) + "x" + to_string(GetSelectedAreaHeight()) + "s";
	const char* save_size = size.c_str();
	WriteFile(write_save_file, save_size, strlen(save_size), &bytes_written, NULL);

	for (int i = GetSelectionStartX(); i < GetSelectionEndX(); i++) {
		for (int j = GetSelectionStartY(); j < GetSelectionEndY(); j++) {
			save_data_int = GetMatrix(i, j);
			save_data_string = DecToHex(save_data_int);
			if (save_data_string.size() == 5) {
				save_data_string = "0" + save_data_string;
			}
			else if (save_data_string.size() == 4) {
				save_data_string = "00" + save_data_string;
			}
			save_data_char = save_data_string.c_str();

			WriteFile(write_save_file, save_data_char, strlen(save_data_char), &bytes_written, NULL);
		}
	}

	CloseHandle(write_save_file);
}
