#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)


//Functions to Get and Set Screen Size//

int screen_width;
int screen_height;

internal int
GetScreenWidth() {
	return screen_width;
}

internal void
SetScreenWidth(int new_screen_width) {
	screen_width = new_screen_width;
}

internal int
GetScreenHeight() {
	return screen_height;
}

internal void
SetScreenHeight(int new_screen_height) {
	screen_height = new_screen_height;
}

//End Screen Size//
//Function to Get the Cursor Position//

POINT cursor_position;

internal int GetCursorX() {
	GetCursorPos(&cursor_position);
	ScreenToClient(FindWindowA("Graphics Window Class", "My First Engine!"), &cursor_position);
	return cursor_position.x;
}
internal int GetCursorY() {
	GetCursorPos(&cursor_position);
	ScreenToClient(FindWindowA("Graphics Window Class", "My First Engine!"), &cursor_position);
	return GetScreenHeight() - cursor_position.y;
}

//----------------------------------//
// //Class to Store and Render Sprites//
class Sprites
{
private:
	bool include_sprite = false;
	u32 sprite_width = NULL;
	u32 sprite_height = NULL;
	float sprite_pixel_width = NULL;
	float sprite_pixel_height = NULL;
	vector<vector<u32>> sprite = vector<vector<u32>>();
	string sprite_name = "";
	string sprite_save_data = "";
public:
	void SetSpriteName(string new_sprite_name) {
		sprite_name = "..\\Save_Files\\" + new_sprite_name + ".txt";
	}
	string GetSpriteName() {
		return sprite_name;
	}

	void SetSpriteWidth(u32 new_width) {
		sprite_width = new_width;
	}
	u32 GetSpriteWidth() {
		return sprite_width;
	}

	void SetSpriteHeight(u32 new_height) {
		sprite_height = new_height;
	}
	u32 GetSpriteHeight() {
		return sprite_height;
	}

	void SetSpritePixelWidth(float new_pixel_width) {
		sprite_pixel_width = new_pixel_width;
	}
	u32 GetSpritePixelWidth() {
		return sprite_pixel_width;
	}
	void SetSpritePixelHeight(float new_pixel_height) {
		sprite_pixel_height = new_pixel_height;
	}
	u32 GetSpritePixelHeight() {
		return sprite_pixel_height;
	}

	void SetSpriteIncluded(bool is_included) {
		include_sprite = is_included;
	}
	bool GetSpriteIncluded() {
		return include_sprite;
	}

	void SetSpriteSaveData(string new_sprite_data) {
		sprite_save_data = new_sprite_data;
	}
	string GetSpriteSaveData() {
		return sprite_save_data;
	}

	string GetNextSpriteColour() {
		string next_colour;
		next_colour = "";

		for (int i = 0; i < 6; i++) {
			string data = GetSpriteSaveData();
			next_colour += data[0];
			RemoveSpriteData(0, 1);
		}

		return next_colour;
	}

	vector<vector<u32>> GetSprite() {
		return sprite;
	}
	u32 GetSpriteColour(u32 i, u32 j) {
		return sprite[i][j];
	}

	void RemoveSpriteData(s32 index, s32 length) {
		string copy = GetSpriteSaveData();
		copy.erase(index, length);
		SetSpriteSaveData(copy);
	}

	void AddSprite(string sprite_save_name) {
		SetSpriteName(sprite_save_name);
		StoreSprite();
	}

	void StoreSprite() {
		const char* sprite_file_name = sprite_name.c_str();
		DWORD file_exists = GetFileAttributes(sprite_file_name);
		if (file_exists != 0xffffffff) {
			DWORD bytes_read;
			BYTE buffer[10];

			HANDLE read_save_file_length = CreateFile(sprite_file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			ReadFile(read_save_file_length, buffer, sizeof(buffer), &bytes_read, NULL);

			SetSpriteSaveData((char*)buffer);

			string width = "";
			string height = "";
			bool getting_width = true;
			bool getting_height = true;

			while (getting_width) {
				string data_with_size = GetSpriteSaveData();
				char next_letter = data_with_size[0];
				if (next_letter == 'x') {
					RemoveSpriteData(0, 1);
					getting_width = true;
					break;
				}
				width += data_with_size[0];
				RemoveSpriteData(0, 1);
			}

			while (getting_height) {
				string data_with_size = GetSpriteSaveData();
				char next_letter = data_with_size[0];
				if (next_letter == 's') {
					RemoveSpriteData(0, 1);
					getting_height = true;
					break;
				}
				height += data_with_size[0];
				RemoveSpriteData(0, 1);
			}

			CloseHandle(read_save_file_length);

			SetSpriteWidth(stoi(width));
			SetSpriteHeight(stoi(height));

			sprite.resize(GetSpriteWidth());
			for (int i = 0; i < sprite.size(); i++) {
				sprite[i].resize(GetSpriteHeight());
			}

			u32 file_size_length = width.length() + height.length() + 2;
			u32 buffer_length = file_size_length + (6 * GetSpriteHeight() * GetSpriteWidth());

			BYTE* new_buffer = new BYTE[buffer_length];

			HANDLE read_save_file = CreateFile(sprite_file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			long file_size = GetFileSize(read_save_file, NULL);
			ReadFile(read_save_file, new_buffer, file_size, &bytes_read, NULL);

			SetSpriteSaveData((char*)new_buffer);
			RemoveSpriteData(0, file_size_length);

			string load_colour_string;

			for (u32 i = 0; i < GetSpriteWidth(); i++) {
				for (u32 j = 0; j < GetSpriteHeight(); j++) {
					load_colour_string = "0x" + GetNextSpriteColour();
					u32 load_colour_hex = stoi(load_colour_string, 0, 16);
					sprite[i][j] = load_colour_hex;
				}
			}

			CloseHandle(read_save_file);
			SetSpriteIncluded(true);
		}
	}
};


//End Sprite Class 
//Box Class//

class Shape : public Sprites
{
private:
	u32 position_x;
	u32 position_y;
	u32 width;
	u32 height;
	u32 box_colour;
	bool borders[4];
	u32 border_colour;
	vector<string> box_text;
	u32 box_text_colour;
	u32 box_text_size;
	u32 box_text_x;
	u32 box_text_y;
	u32 box_text_lines;
	bool text_centred_y;
	bool hide_box;
	vector<float> *box_text_widths = new vector<float>;
public:
	void CreateShape(u32 new_position_x,
		u32 new_position_y,
		u32 new_width,
		u32 new_height,
		u32 new_box_colour,
		bool new_borders_on,
		u32 new_border_colour) 
	{
		position_x = new_position_x;
		position_y = new_position_y;
		height = new_height;
		width = new_width;
		box_colour = new_box_colour;
		borders[0] = new_borders_on;
		borders[1] = new_borders_on;
		borders[2] = new_borders_on;
		borders[3] = new_borders_on;
		border_colour = new_border_colour;
		box_text;
		box_text_colour = 0x000000;
		box_text_size = 4;
		box_text_x = new_position_x;
		box_text_y = new_position_y;
		hide_box = false;
	}

	void SetPosition_x(u32 new_position_x) {
		position_x = new_position_x;
	}
	u32 GetPosition_x() {
		return position_x;
	}

	void SetPosition_y(u32 new_position_y) {
		position_y = new_position_y;
	}
	u32 GetPosition_y() {
		return position_y;
	}

	void SetWidth(u32 new_length) {
		width = new_length;
	}
	u32 GetWidth() {
		return width;
	}

	void SetHeight(u32 new_height) {
		height = new_height;
	}
	u32 GetHeight() {
		return height;
	}

	void SetBoxColour(u32 new_colour) {
		box_colour = new_colour;
	}
	u32 GetBoxColour() {
		return box_colour;
	}

	void SetBorderColour(u32 new_colour) {
		border_colour = new_colour;
	}
	u32 GetBorderColour() {
		return border_colour;
	}

	void SetBoxText(vector<string> new_box_text) {
		for (int line = 0; line < new_box_text.size(); line++) {
			box_text[line] = new_box_text[line];
		}
	}
	vector<string> GetBoxText() {
		return box_text;
	}

	void SetTextColour(u32 new_colour) {
		box_text_colour = new_colour;
	}
	u32 GetTextColour() {
		return box_text_colour;
	}

	void SetBoxTextSize(u32 new_size) {
		box_text_size = new_size;
	}
	u32 GetBoxTextSize() {
		return box_text_size;
	}

	void SetBoxTextX(u32 new_x) {
		box_text_x = new_x;
	}
	u32 GetBoxTextX() {
		return(box_text_x);
	}

	void SetBoxTextY(u32 new_y) {
		box_text_y = new_y;
	}
	u32 GetBoxTextY() {
		return(box_text_y);
	}

	void SetBoxLines(u32 number_of_lines) {
		box_text_lines = number_of_lines;
	}
	u32 GetBoxLines() {
		return(box_text_lines);
	}

	void SetHideBox(bool do_hide_box) {
		hide_box = do_hide_box;
	}
	bool GetHideBox() {
		return hide_box;
	}

	void HideBox() {
		SetHideBox(true);
	}

	void SetBoxTextWidth(vector<string> new_text) {
		vector<const char*> text;
		u32 letter_width = 1;
		vector<float> line_widths;
		for (int i = 0; i < new_text.size(); i++) {
			text.push_back(new_text[i].c_str());
			line_widths.push_back(0);
		}

		for (int line = 0; line < text.size(); line++) {
			while (*text[line]) {
				const char** a_letter = numbers_letters_symbols[*text[line] - ' '];
				line_widths[line] += strlen(*a_letter);
				letter_width = max(letter_width, (strlen(*a_letter)));
				text[line]++;
				letter_width = 1;
			}
		}
		*box_text_widths = line_widths;
	}

	vector<float> GetBoxTextWidth() {
		return *box_text_widths;
	}
	
	void AddBlanks(int current_line, int length) {
		for (int blanks = 0; blanks <= length; blanks++) {
			box_text[current_line] = " " + box_text[current_line] + " ";			
		}
		SetBoxTextWidth(box_text);
	}

	void ExpandToCentre() {
		u32 longest_line = 0;
		for (int i = 0; i < box_text.size(); i++) {
			longest_line = max(longest_line, GetBoxTextWidth()[i]);
		}
		u32 current_line_length;
		int length_difference;

		for (int line = 0; line < box_text.size(); line++) {
			current_line_length = GetBoxTextWidth()[line];
			if (current_line_length < longest_line) {
				length_difference = (longest_line - current_line_length) / 2;
				AddBlanks(line, length_difference);
			}
		}
	}	

	void XFromLeft(u32 from_left) {
		box_text_x = GetPosition_x() + from_left;
	}
	void XFromRight(u32 from_right) {
		box_text_x = GetPosition_x() + GetWidth() - from_right;
	}
	void YFromTop(u32 from_top) {
		box_text_y = GetPosition_y() + GetHeight() - from_top;
		text_centred_y = false;
	}
	void YFromBottom(u32 from_bottom) {
		box_text_y = GetPosition_y() + (GetHeight() / 2) + from_bottom;
		text_centred_y = false;
	}
	void XCentred() {	
		ExpandToCentre();
		box_text_x = GetPosition_x() + (GetWidth() / 2) - (GetBoxTextWidth()[0] * box_text_size) / 1.65;
	}
	void YCentred() {		
		if (box_text.size() == 1) box_text_y = GetPosition_y() + (GetHeight() / 2) + (box_text_size * 2.5);
		else box_text_y = GetPosition_y() + (GetHeight() / 2) + (box_text.size() * box_text_size * 3.5);
		text_centred_y = true;
	}

	void AddBoxText(vector<string> new_text, u32 new_text_colour, u32 new_text_size, string x_position_from_ieLEFT, u32 x_from, string y_position_from_ieTOP, u32 y_from) {
		box_text = new_text;
		box_text_colour = new_text_colour;
		box_text_size = new_text_size;
		SetBoxTextWidth(new_text);

		if (x_position_from_ieLEFT == "LEFT") {
			XFromLeft(x_from);
		}
		else if (x_position_from_ieLEFT == "RIGHT") {
			XFromRight(x_from);
		}
		else if (x_position_from_ieLEFT == "CENTRE") {
			XCentred();
		}
		else {
			box_text_x = GetPosition_x();
		}

		if (y_position_from_ieTOP == "TOP") {
			YFromTop(y_from);
		}
		else if (y_position_from_ieTOP == "BOTTOM") {
			YFromBottom(y_from);
		}
		else if (y_position_from_ieTOP == "CENTRE") {
			YCentred();
		}
		else {
			box_text_y = GetPosition_y();
		}
	}

	void SetAllBorders(bool are_shown) {
		for (int i = 0; i < 4; i++) {
			borders[i] = are_shown;
		}
	}
	void SetLBorder(bool left) {
		borders[0] = left;
	}
	void SetRBorder(bool right) {
		borders[1] = right;
	}
	void SetTBorder(bool top) {
		borders[2] = top;
	}
	void SetBBorder(bool bottom) {
		borders[3] = bottom;
	}
	bool* GetBorders() {
		return borders;
	}

	void RenderBox(bool from_centre) {
		if (GetHideBox()) {
			DrawLettersText(GetBoxText(), GetBoxTextX(), GetBoxTextY(), GetBoxTextSize(), GetTextColour());
		}
		else if (!GetSpriteIncluded()){
			if (!from_centre) {
				DrawRect(GetPosition_x(), GetPosition_y(), GetWidth() / 2, GetHeight() / 2, GetBoxColour());
				if (GetBorders()[0]) {
					DrawRect(GetPosition_x(), GetPosition_y() - 1, 1, GetHeight() / 2 + 1, GetBorderColour());
				}
				if (GetBorders()[1]) {
					DrawRect(GetPosition_x() - 1 + GetWidth(), GetPosition_y() - 1, 1, GetHeight() / 2 + 1, GetBorderColour());
				}
				if (GetBorders()[2]) {
					DrawRect(GetPosition_x(), GetPosition_y() - 1, GetWidth() / 2, 1, GetBorderColour());
				}
				if (GetBorders()[3]) {
					DrawRect(GetPosition_x(), GetPosition_y() + GetHeight() - 1, GetWidth() / 2 + 0.5, 1, GetBorderColour());
				}
				if (GetBoxText().size() != 0)
				{
					DrawLettersText(GetBoxText(), GetBoxTextX(), GetBoxTextY(), GetBoxTextSize(), GetTextColour());
				}
			}
			if (from_centre) {
				DrawRect(GetPosition_x() - GetWidth() / 2, GetPosition_y() - GetHeight() / 2, GetWidth() / 2, GetHeight() / 2, GetBoxColour());
				if (GetBorders()[0]) {
					DrawRect(GetPosition_x() - GetWidth() / 2, GetPosition_y() - 1 - GetHeight() / 2, 1, GetHeight() / 2 + 1, GetBorderColour());
				}
				if (GetBorders()[1]) {
					DrawRect(GetPosition_x() - 1 + GetWidth() - GetWidth() / 2, GetPosition_y() - 1 - GetHeight() / 2, 1, GetHeight() / 2 + 1, GetBorderColour());
				}
				if (GetBorders()[2]) {
					DrawRect(GetPosition_x() - GetWidth() / 2, GetPosition_y() - 1 - GetHeight() / 2, GetWidth() / 2, 1, GetBorderColour());
				}
				if (GetBorders()[3]) {
					DrawRect(GetPosition_x() - GetWidth() / 2, GetPosition_y() + GetHeight() - 1 - GetHeight() / 2, GetWidth() / 2 + 0.5, 1, GetBorderColour());
				}
				if (GetBoxText().size() != 0)
				{
					DrawLettersText(GetBoxText(), GetBoxTextX() - GetWidth() / 2, GetBoxTextY() - GetHeight() / 2, GetBoxTextSize(), GetTextColour());
				}
			}
		}	
		else {
			SetSpritePixelWidth(GetWidth() / float(GetSpriteWidth()));
			SetSpritePixelHeight(GetHeight() / float(GetSpriteHeight()));
			if (!from_centre) {
				for (int i = 0; i < GetSpriteWidth(); i++) {
					for (int j = 0; j < GetSpriteHeight(); j++) {
						if (GetSpriteColour(i, j) != 0xF1F1F1)
							DrawRect(GetPosition_x() + (GetSpritePixelWidth() * i), GetPosition_y() + (GetSpritePixelHeight() * j), GetSpritePixelWidth(), GetSpritePixelHeight(), GetSpriteColour(i, j));
					}
				}
			}
			else {
				for (int i = 0; i < GetSpriteWidth(); i++) {
					for (int j = 0; j < GetSpriteHeight(); j++) {
						if (GetSpriteColour(i, j) != 0xF1F1F1)
							DrawRect(GetPosition_x() - (GetWidth() / 2) + (GetSpritePixelWidth() * i), GetPosition_y() - (GetHeight() / 2) + (GetSpritePixelHeight() * j), GetSpritePixelWidth(), GetSpritePixelHeight(), GetSpriteColour(i, j));
					}
				}
			}
		}
	}

	float xRight;
	float r2;
	float y2;

	void RenderCircle(bool from_centre) {
		if (GetHideBox()) {

		}
		else {
			for (float y = 0; y < width; y += 0.1) {
				r2 = pow((width / 2), 2);
				y2 = pow(y, 2);
				xRight = sqrt(r2 - y2);
				if (from_centre) {
					if (GetBorders()[0]) {
						DrawRect(GetPosition_x() - (xRight)-1, GetPosition_y() + y + 1, xRight + 1, 0.1, 0x000000);
						DrawRect(GetPosition_x() - (xRight)-1, GetPosition_y() - y - 1, xRight + 1, 0.1, 0x000000);
					}

					DrawRect(GetPosition_x() - (xRight), GetPosition_y() + y, xRight, 0.1, GetBoxColour());
					DrawRect(GetPosition_x() - (xRight), GetPosition_y() - y, xRight, 0.1, GetBoxColour());
				}
				else {
					if (GetBorders()[0]) {
						DrawRect(GetPosition_x() - (xRight)+(width / 2) - 1, GetPosition_y() + y + (width / 2) + 1, xRight + 1, 0.1, GetBoxColour());
						DrawRect(GetPosition_x() - (xRight)+(width / 2) - 1, GetPosition_y() - y + (width / 2) - 1, xRight + 1, 0.1, GetBoxColour());
					}
					DrawRect(GetPosition_x() - (xRight)+(width / 2), GetPosition_y() + y + (width / 2), xRight, 0.1, GetBoxColour());
					DrawRect(GetPosition_x() - (xRight)+(width / 2), GetPosition_y() - y + (width / 2), xRight, 0.1, GetBoxColour());
				}

			}
		}

	}
};

//End Shape Class// 
//Brush Class//

class PaintBrush : public Shape
{
public:
	u32 brush_size = 1;
	u32 brush_type = 2;
	u32 stored_brush_type = 0;
	u32 stored_brush_size = 1;
	u32 stored_brush_colour = 0x000000;

	void SetBrushSize(u32 new_size) {
		switch (new_size) {
			case 1: {
				SetWidth(GetScreenWidth() * 0.01);
				SetHeight(GetScreenWidth() * 0.01);
				brush_size = 1;  
				break;
			}
			case 2: {
				SetWidth(GetScreenWidth() * 0.03); 
				SetHeight(GetScreenWidth() * 0.03);
				brush_size = 2;
				break;
			}
			case 3: {
				SetWidth(GetScreenWidth() * 0.05); 
				SetHeight(GetScreenWidth() * 0.05);
				brush_size = 3;
				break;
			}
			default: {
				SetWidth(GetScreenWidth() * 0.01); 
				SetHeight(GetScreenWidth() * 0.01);
				brush_size = 1;
				break;
			}
		}	
	}

	u32 GetBrushSize() {
		return brush_size;
	}

	void SetBrushType(u32 new_type) {
		brush_type = new_type;
	}

	u32 GetBrushType() {
		return brush_type;
	}

	void StoreBrush() {
		if (brush_type != 0 && brush_type != 4) {
			stored_brush_colour = GetBoxColour();
			stored_brush_type = GetBrushType();
			stored_brush_size = GetBrushSize();
		}
	}
	void RestoreBrush() {
		SetBrushType(stored_brush_type);
		SetBrushSize(stored_brush_size);
		SetBoxColour(stored_brush_colour);
	}
};

//End Brush Class//
//Button Class//

class Button : public Shape
{
public:
	bool ButtonSelected() {
		if (GetCursorX() > GetPosition_x() &&
			GetCursorX() < GetPosition_x() + GetWidth() &&
			GetCursorY() > GetPosition_y() &&
			GetCursorY() < GetPosition_y() + GetHeight() &&
			((GetKeyState(VK_LBUTTON) & 0x8000) != 0)) {
				return true;
			}
		else return false;
	}	
	bool CentredButtonSelected() {
		if (GetCursorX() > GetPosition_x() - (GetWidth() / 2) &&
			GetCursorX() < GetPosition_x() + (GetWidth() / 2) &&
			GetCursorY() > GetPosition_y() - (GetHeight() / 2) &&
			GetCursorY() < GetPosition_y() + (GetHeight() / 2) &&
			((GetKeyState(VK_LBUTTON) & 0x8000) != 0)) {
			return true;
		}
		else return false;
	}
	bool ButtonRightClicked() {
		if (GetCursorX() > GetPosition_x() &&
			GetCursorX() < GetPosition_x() + GetWidth() &&
			GetCursorY() > GetPosition_y() &&
			GetCursorY() < GetPosition_y() + GetHeight() &&
			((GetKeyState(VK_RBUTTON) & 0x8000) != 0)) {
			return true;
		}
		else return false;
	}
};

//End Button Class//
//Text Input Box Class//

class TextInput : public Button
{
private: 
	vector<string> *new_input_text = new vector<string>();
	bool include_description;
public:	
	bool IncludeDescription() {
		return include_description;
	}

	void SetDescription(string new_description) {
		include_description = true;
		if (new_input_text->size() == 0)
			new_input_text->push_back(new_description);
		else new_input_text->at(0) = new_description;
	}
	
	void AddText(string new_text) {
		if (IncludeDescription()) {
			if (new_input_text->size() == 1)
				new_input_text->push_back(new_text);
			else {
				if (new_input_text->at(1).length() > 5)
					return;

				new_input_text->at(1) += new_text;
			}
			new_input_text->at(0) = GetBoxText()[0];
		}
		else {
			if (new_input_text->size() == 0)
				new_input_text->push_back(new_text);
			else {
				if (new_input_text->at(0).length() > 5)
					return;

				new_input_text->at(0) += new_text;
			}			
		}
	}

	void ClearText() {
		if (IncludeDescription()) {
			if (new_input_text->size() == 2)
				new_input_text->at(1) = "";
		}
		else {
			if (new_input_text->size() == 1)
				new_input_text->at(0) = "";
		}
	}

	void RemoveText() {
		if (IncludeDescription()) {
			if (new_input_text->at(1) != "") new_input_text->at(1).pop_back();
		}
		else {
			if (new_input_text->at(0) != "") new_input_text->at(0).pop_back();
		}
	}

	vector<string> GetInputText() {
		return *new_input_text;
	}

	void UpdateText() {
		SetBoxText(*new_input_text);
	}
};

//End Text Input Box Class// 
//Class to Create Sliders//

class Slider : public Button
{
public:	
	u32 slider_position_x;
	u32 slider_position_y;
	u32 slider_height;
	u32 slider_width;
	u32 slider_colour;
	u32 slider_border_colour;
	bool slider_borders[4];

	void CreateSlider(u32 new_position_x,
		u32 new_position_y,
		u32 new_width,
		u32 new_height,
		u32 new_box_colour,
		bool new_borders_on,
		u32 new_border_colour)
	{
		slider_position_x = new_position_x;
		slider_position_y = new_position_y;
		slider_height = new_height;
		slider_width = new_width;
		slider_colour = new_box_colour;
		slider_borders[0] = new_borders_on;
		slider_borders[1] = new_borders_on;
		slider_borders[2] = new_borders_on;
		slider_borders[3] = new_borders_on;
		slider_border_colour = new_border_colour;
	}

	void SetSliderWidth(u32 new_slider_width) {
		slider_width = new_slider_width;
	}
	u32 GetSliderWidth() {
		return slider_width;
	}

	void SetSliderHeight(u32 new_slider_height) {
		slider_height = new_slider_height;
	}
	u32 GetSliderHeight() {
		return slider_height;
	}

	void SetSliderPosition_x(u32 new_slider_position_x) {
		slider_position_x = new_slider_position_x;
	}
	u32 GetSliderPosition_x() {
		return slider_position_x;
	}

	void SetSliderPosition_y(u32 new_slider_position_y) {
		slider_position_y = new_slider_position_y;
	}
	u32 GetSliderPosition_y() {
		return slider_position_y;
	}

	void SetSliderBoxColour(u32 new_colour) {
		slider_colour = new_colour;
	}
	u32 GetSliderBoxColour() {
		return slider_colour;
	}

	void SetSliderBorderColour(u32 new_colour) {
		slider_border_colour = new_colour;
	}
	u32 GetSliderBorderColour() {
		return slider_border_colour;
	}

	void SetAllSliderBorders(bool are_shown) {
		for (int i = 0; i < 4; i++) {
			slider_borders[i] = are_shown;
		}
	}
	void SetLSliderBorder(bool left) {
		slider_borders[0] = left;
	}
	void SetRSliderBorder(bool right) {
		slider_borders[1] = right;
	}
	void SetTSliderBorder(bool top) {
		slider_borders[2] = top;
	}
	void SetBSliderBorder(bool bottom) {
		slider_borders[3] = bottom;
	}
	bool* GetSliderBorders() {
		return slider_borders;
	}

	void RenderSlider() {
		DrawRect(GetSliderPosition_x(), GetSliderPosition_y(), GetSliderWidth() / 2, GetSliderHeight() / 2, GetSliderBoxColour());
		if (GetSliderBorders()[0]) {
			DrawRect(GetSliderPosition_x(), GetSliderPosition_y() - 1, 1, GetSliderHeight() / 2 + 1, GetSliderBorderColour());
		}
		if (GetSliderBorders()[1]) {
			DrawRect(GetSliderPosition_x() -1 + GetSliderWidth(), GetSliderPosition_y() - 1, 1, GetSliderHeight() / 2 + 1, GetSliderBorderColour());
		}
		if (GetSliderBorders()[3]) {
			DrawRect(GetSliderPosition_x(), GetSliderPosition_y() - 1, GetSliderWidth() / 2, 1, GetSliderBorderColour());
		}
		if (GetSliderBorders()[2]) {
			DrawRect(GetSliderPosition_x(), GetSliderPosition_y() - 1 + GetSliderHeight(), GetSliderWidth() / 2 + 0.5, 1, GetSliderBorderColour());
		}
	}
};

//End of Slider Class//
//Straight Line Class//

class StraightLine
{
public:
	float angle = NULL;
	float gradient = NULL;
	float start_x = NULL;
	float end_x = NULL;
	float temporary_x = NULL;
	float current_y = NULL;
	float start_y = NULL;
	float end_y = NULL;
	float temporary_y = NULL;
	float line_width = NULL;
	float line_length = NULL;
	u32 line_colour = 0x000000;

	void CreateLineByPoints(float x1, float y1, float x2, float y2, u32 set_width, u32 set_colour) {
		SetStartX(x1); SetStartY(y1); SetEndX(x2); SetEndY(y2); SetLineWidth(set_width); SetColour(set_colour);
		if (y2 < y1 && x2 > x1) {
			
		}
		else if (x2 < x1 || y2 < y1) {
			start_x = x2; end_x = x1;	start_y = y2; end_y = y1;	
		}
		float dy = y2 - y1;
		float dx = x2 - x1;
		gradient = dy / dx;
	}

	void CreateLineByGradient(u32 x1, u32 y1, u32 set_gradient, u32 set_length, u32 set_width, u32 set_colour) {
		SetStartX(x1); SetStartY(y1); SetGradient(set_gradient); SetLineLength(set_length); SetLineWidth(set_width); SetColour(set_colour);
		end_x = x1 + (set_length / sqrt(1 + pow(set_gradient, 2)));
	}

	void CreateLineByAngle(u32 x1, u32 y1, u32 set_angle_degrees, u32 set_length, u32 set_width, u32 set_colour) {
		SetStartX(x1); SetStartY(y1); SetAngle(set_angle_degrees); SetLineLength(set_length); SetLineWidth(set_width); SetColour(set_colour);
		gradient = (atan(90 - angle));
		end_x = (x1 + (set_length / sqrt(1 + pow(gradient, 2))));
	}

	void SetGradient(u32 new_gradient) {
		gradient = new_gradient;
	}
	u32 GetGradient() {
		return gradient;
	}

	void SetAngle(u32 new_angle) {
		angle = new_angle;;
	}
	u32 GetAngle() {
		return angle;
	}

	void SetStartX(u32 new_start_x) {
		start_x = new_start_x;
	}
	u32 GetStartX() {
		return start_x;
	}

	void SetStartY(u32 new_start_y) {
		start_y = new_start_y;
	}
	u32 GetStartY() {
		return start_y;
	}

	void SetEndX(u32 new_end_x) {
		end_x = new_end_x;
	}
	u32 GetEndX() {
		return end_x;
	}

	void SetEndY(u32 new_end_y) {
		end_y = new_end_y;
	}
	u32 GetEndY() {
		return end_y;
	}

	void SetLineWidth(u32 new_width) {
		line_width = new_width;
	}
	u32 GetLineWidth() {
		return line_width;
	}

	void SetLineLength(u32 new_length) {
		line_length = new_length;
	}
	u32 GetLineLength() {
		return line_length;
	}

	void SetColour(u32 new_colour) {
		line_colour = new_colour;
	}
	u32 GetColour() {
		return line_colour;
	}

	void RenderLine() {
		if (start_x == end_x) {
			DrawRect(start_x, start_y, line_width, (end_y - start_y) / 2, line_colour);
		}
		else if (start_y == end_y) {
			DrawRect(start_x, start_y, (end_x - start_x) / 2, line_width, line_colour);
		}
		else {
			for (float current_x = start_x; current_x < end_x; current_x += 0.1) {
				current_y = gradient * (current_x - start_x) + start_y;
				DrawRect(current_x, current_y, line_width, line_width, line_colour);
			}
		}
	}
};
//End of Straight Line Class//
//Keys Class//

class Keys
{
public:
	bool held = true;

	bool GetHeld() {
		if (held) return true;
		else if (!held) return false;
	}

	void SetHeld(bool is_held) {
		held = is_held;
	}
};

//End Keys Class//

