//All global functions and variables
//Function to Convert Decimal numbers to Hexadecimal, By GeeksForGeeks
internal string
DecToHex(int n)
{
	// ans string to store hexadecimal number
	string ans = "";

	if (n == 0) {
		return "000000";
	}

	while (n != 0) {
		// remainder variable to store remainder
		int rem = 0;

		// ch variable to store each character
		char ch;
		// storing remainder in rem variable.
		rem = n % 16;

		// check if temp < 10
		if (rem < 10) {
			ch = rem + 48;
		}
		else {
			ch = rem + 55;
		}

		// updating the ans string with the character variable
		ans += ch;
		n = n / 16;
	}

	// reversing the ans string to get the final result
	int i = 0, j = ans.size() - 1;
	while (i <= j)
	{
		swap(ans[i], ans[j]);
		i++;
		j--;
	}
	return ans;
}

//End of Hex Conversion 
//Function To Test if Button is Pressed Not Held 

bool first_time;

internal bool
IsPressed(Input* input, u32 button) {
	if (input->buttons[button].is_down && first_time) {
		first_time = false;
		return true;
	}
}

//End of Function//
//Check if Menu is Open//
bool menus_open = false;

internal void
SetMenuOpen(bool is_open) {
	menus_open = is_open;
}
internal bool
GetMenuOpen() {
	return menus_open;
}

//End Matrix// 
//Matrix Functions//

u32 matrix_width;
u32 matrix_height;
float matrix_pixel_size;

internal void
SetMatrixWidth(u32 new_width) {
	matrix_width = new_width;
}

internal u32
GetMatrixWidth() {
	return matrix_width;
}

internal void
SetMatrixHeight(u32 new_height) {
	matrix_height = new_height;
}
internal u32
GetMatrixHeight() {
	return matrix_height;
}

internal void
SetPixelSize(float new_size) {
	matrix_pixel_size = new_size;
}

internal float
GetPixelSize() {
	return matrix_pixel_size;
}

vector<vector<u32>> matrix(matrix_width, vector<u32>(matrix_height, 0));
vector<vector<u32>> matrix_copy(matrix_width, vector<u32>(matrix_height, 0));

internal void
CreateMatrix() {
	matrix.resize(matrix_width);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].resize(matrix_height);
	}
	for (int i = 0; i < GetMatrixWidth(); i++) {
		for (int j = 0; j < GetMatrixHeight(); j++) {
			matrix[i][j] = 0xF1F1F1;
		}
	}
}

internal void
ClearMatrix() {
	for (int i = 0; i < GetMatrixWidth(); i++) {
		for (int j = 0; j < GetMatrixHeight(); j++) {
			matrix[i][j] = 0xF1F1F1;
		}
	}
}

internal void
SetMatrixSize(u32 new_width, u32 new_height) {
	matrix_width = new_width;
	matrix_height = new_height;
	u32 square_matrix_size = max(new_width, new_height);
	matrix.resize(square_matrix_size);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].resize(square_matrix_size);
	}
	for (int i = 0; i < square_matrix_size; i++) {
		for (int j = 0; j < square_matrix_size; j++) {
			if (i <= matrix_width || j <= matrix_height) matrix[i][j] = 0xF1F1F1;
		}
	}
}

internal int
GetMatrix(int i, int j) {
	return matrix[i][j];
}

internal void
SetWholeMatrix(vector<vector<u32>> new_matrix) {
	matrix = new_matrix;
}
internal vector<vector<u32>>
GetWholeMatrix() {
	return matrix;
}

u32 brush_size_in_pixels;
float radius2;
float height2;
u32 circle_x;

internal void
SetMatrix(int i, int j, u32 colour, u32 brush_size /*1 = 1 pixel, 2 = medium, 3 = large*/, u32 brush_shape /*1 = square, 2 = circle*/) {
	switch (brush_size) {
	case 1: matrix[i][j] = colour; brush_size_in_pixels = 1; break;
	case 2: brush_size_in_pixels = ceil(GetScreenWidth() * 0.03 / GetPixelSize()) / 2; break;
	case 3: brush_size_in_pixels = GetScreenWidth() * 0.05 / GetPixelSize() / 2; break;
	default: brush_size_in_pixels = 1; break;
	}	
	if (brush_size_in_pixels <= 1) {
		matrix[i][j] = colour;
	}
	else {
		switch (brush_shape) {
		case 1: {
			for (int x = 0; x < brush_size_in_pixels; x++) {
				for (int y = 0; y < brush_size_in_pixels; y++) {
					if (i - x < 0 || i + x >= GetMatrixWidth() || j - y < 0 || j + y >= GetMatrixHeight()) {
						break;
					}
					matrix[i - x][j - y] = colour;
					matrix[i + x][j + y] = colour;
					matrix[i - x][j + y] = colour;
					matrix[i + x][j - y] = colour;
					matrix[i + x][j] = colour;
					matrix[i - x][j] = colour;
					matrix[i][j + y] = colour;
					matrix[i][j - y] = colour;
				}
			}
		}
		case 2: {
			for (int x = 0; x < brush_size_in_pixels; x++) {
				for (int y = 0; y < brush_size_in_pixels; y++) {
					if (i - x < 0 || i + x >= GetMatrixWidth() || j - y < 0 || j + y >= GetMatrixHeight()) {
						break;
					}
					radius2 = pow(x, 2);
					height2 = pow(y, 2);
					circle_x = sqrt(radius2 - height2);
					for (int z = 0; z <= circle_x; z++) {
						matrix[i - z][j - y] = colour;
						matrix[i + z][j + y] = colour;
						matrix[i - z][j + y] = colour;
						matrix[i + z][j - y] = colour;
					}

				}
			}
		}
	}
	}
}

s32 matrix_x;
s32 matrix_y;

internal void
SetMatrixPositionX(s32 new_matrix_x) {
	matrix_x = new_matrix_x;
}
internal s32
GetMatrixPositionX() {
	return matrix_x;
}

internal void
SetMatrixPositionY(s32 new_matrix_y) {
	matrix_y = new_matrix_y;
}
internal s32
GetMatrixPositionY() {
	return matrix_y;
}

bool line_started = false;
bool line_finished = false;
float matrix_gradient;
float matrix_x1;
float matrix_x2;
float matrix_y1;
float matrix_y2;
u32 line_to_draw_x1;
u32 line_to_draw_x2;
u32 line_to_draw_y1;
u32 line_to_draw_y2;
float temp_x1;
float temp_y1;
StraightLine line_to_draw;

internal void
SetMatrixLine(u32 i, u32 j, u32 colour, u32 click_number) {
	if (!line_started && click_number == 1) {
		matrix_x1 = i;
		line_to_draw_x1 = GetCursorX();
		matrix_y1 = j;
		line_to_draw_y1 = GetCursorY();
		line_started = true;
	}
	if (click_number == 1){
		matrix_x2 = i;
		line_to_draw_x2 = GetCursorX();
		matrix_y2 = j;
		line_to_draw_y2 = GetCursorY();
		line_to_draw.CreateLineByPoints(line_to_draw_x1, line_to_draw_y1, line_to_draw_x2, line_to_draw_y2, 1, colour);
		line_to_draw.RenderLine();
	}
	
	if (click_number == 2) {
		if (matrix_x2 < matrix_x1) {
			temp_x1 = matrix_x1; temp_y1 = matrix_y1;
			matrix_x1 = matrix_x2; matrix_y1 = matrix_y2;
			matrix_x2 = temp_x1; matrix_y2 = temp_y1;
		}
		matrix_gradient = (matrix_y2 - matrix_y1) / (matrix_x2 - matrix_x1);
		if (matrix_y2 - matrix_y1 < matrix_x2 - matrix_x1) {
			for (float x = matrix_x1; x < matrix_x2; x += 0.1) {
				float y = floor(matrix_gradient * (x - matrix_x1) + matrix_y1);
				matrix[x][y] = colour;
			}
		}
		else {
			for (float y = matrix_y1; y < matrix_y2; y += 0.1) {
				float x = floor((y - matrix_y1) / matrix_gradient) + matrix_x1;
				matrix[x][y] = colour;
			}
		}
		line_started = false;
	}	
}

internal void
CopyMatrix() {
	matrix_copy = matrix;
}

internal vector<vector<u32>> 
GetCopyMatrix() {
	return matrix_copy;
}

vector<vector<u32>> selected_area(1, vector<u32>(1, 0));
vector<vector<u32>> selected_area_copy(1, vector<u32>(1, 0));
u32 selected_area_width;
u32 selected_area_height;
u32 matrix_select_x1;
u32 matrix_select_x2;
u32 matrix_select_y1;
u32 matrix_select_y2;

internal void 
SetSelectionStartX(u32 start_x) {
	matrix_select_x1 = start_x;
}
internal void
SetSelectionStartY(u32 start_y) {
	matrix_select_y1 = start_y;
}

internal u32
GetSelectionStartX() {
	return matrix_select_x1;
}
internal u32
GetSelectionStartY() {
	return matrix_select_y1;
}

internal void
SetSelectionEndX(u32 end_x) {
	matrix_select_x2 = end_x;
}
internal void
SetSelectionEndY(u32 end_y) {
	matrix_select_y2 = end_y;
}

internal u32
GetSelectionEndX() {
	return matrix_select_x2;
}
internal u32
GetSelectionEndY() {
	return matrix_select_y2;
}

internal void
SetSelectedAreaSize() {
	u32 selected_height = GetSelectionEndY() - GetSelectionStartY();
	u32 selected_width = GetSelectionEndX() - GetSelectionStartX();
	selected_area.resize(selected_width);
	for (int i = 0; i < selected_area.size(); i++) {
		selected_area[i].resize(selected_height);
	}
	selected_area_width = selected_width;
	selected_area_height = selected_height;
}

internal u32
GetSelectedAreaWidth() {
	return selected_area_width;
}
internal u32
GetSelectedAreaHeight() {
	return selected_area_height;
}

internal void
SetSelectedArea() {
	u32 index_x = 0; u32 index_y = 0;

	for (int i = GetSelectionStartX(); i < GetSelectionEndX(); i++) {
		for (int j = GetSelectionStartY(); j < GetSelectionEndY(); j++) {
			selected_area[index_x][index_y] = matrix[i][j];
			index_y++;
		}
		index_x++;
		index_y = 0;
	}
}

internal void
SetMatrixToSelected(u32 initial_x, u32 initial_y) {
	u32 index_x = 0;
	u32 index_y = 0;
	for (int i = initial_x; i < initial_x + GetSelectedAreaWidth(); i++) {
		for (int j = initial_y; j < initial_y + GetSelectedAreaHeight(); j++) {
			if (j < GetMatrixHeight() && i < GetMatrixWidth())
				matrix[i][j] = selected_area[index_x][index_y];
			index_y++;
		}
		index_x++;
		index_y = 0;
	}
}

bool select_started = false;
bool select_finished = false;

internal void
SetSelectStarted(bool is_started) {
	select_started = is_started;
}
internal void
SetSelectFinished(bool is_finished) {
	select_finished = is_finished;
}

u32 select_x1;
u32 select_x2;
u32 select_y1;
u32 select_y2;
u32 coordinate_width;
u32 coordinate_height;

internal u32
GetSelectionX1() {
	return select_x1;
}
internal u32
GetSelectionY1() {
	return select_y1;
}
internal u32
GetSelectionX2() {
	return select_x2;
}
internal u32
GetSelectionY2() {
	return select_y2;
}
internal void
SetSelectionX1(s32 new_x1) {
	select_x1 = new_x1;
}
internal void
SetSelectionX2(s32 new_x2) {
	select_x2 = new_x2;
}
internal void
SetSelectionY1(s32 new_y1) {
	select_y1 = new_y1;
}
internal void
SetSelectionY2(s32 new_y2) {
	select_y2 = new_y2;
}
internal void
SetCoordinateWidth() {
	coordinate_width = max(select_x2, select_x1) - min(select_x1, select_x2);
}
internal void
SetCoordinateHeight() {
	coordinate_height = max(select_y2, select_y1) - min(select_y1, select_y2);
}
internal u32
GetCoordinateWidth() {
	return coordinate_width;
}
internal u32
GetCoordinateHeight() {
	return coordinate_height;
}


u32 matrix_temporary;
StraightLine select_across1;
StraightLine select_across2;
StraightLine select_up1;
StraightLine select_up2;

u32 index_x;
u32 index_y;

internal void 
MatrixSelection(u32 input_x, u32 input_y, u32 click_number) {
	if (click_number == 1 && !select_started) {
		SetSelectionX1(GetCursorX());		
		SetSelectionY1(GetCursorY());
		
		if (input_x <= 0) SetSelectionStartX(0);
		else if (input_x >= matrix_width - 1) SetSelectionStartX(matrix_width - 1);
		else SetSelectionStartX(input_x);

		if (input_y <= 0) SetSelectionStartY(0);
		else if (input_y >= matrix_height - 1) SetSelectionStartY(matrix_height - 1);
		else SetSelectionStartY(input_y);
		
		select_started = true;
		select_finished = false;
	}
	else if (click_number == 1 && select_started) {
		
		SetSelectionX2(GetCursorX());
		SetSelectionY2(GetCursorY());

		select_across1.CreateLineByPoints(select_x1, select_y1, select_x2, select_y1, 2, 0x000000);
		select_across2.CreateLineByPoints(select_x1, select_y2, select_x2, select_y2, 2, 0x000000);
		select_up1.CreateLineByPoints(select_x1, select_y1, select_x1, select_y2, 2, 0x000000);
		select_up2.CreateLineByPoints(select_x2, select_y1, select_x2, select_y2, 2, 0x000000);

		select_across1.RenderLine();
		select_across2.RenderLine();
		select_up1.RenderLine();
		select_up2.RenderLine();

		SetCoordinateHeight();
		SetCoordinateWidth();
	}
	else if (click_number == 2 && !select_finished) {
		if (input_x <= 0) SetSelectionEndX(0);
		else if (input_x >= matrix_width - 1) SetSelectionEndX(matrix_width - 1);
		else SetSelectionEndX(input_x);

		if (input_y <= 0) SetSelectionEndY(0);
		else if (input_y >= matrix_height - 1) SetSelectionEndY(matrix_height - 1);
		else SetSelectionEndY(input_y);

		if (GetSelectionStartX() > GetSelectionEndX()) {
			matrix_temporary = GetSelectionStartX();
			SetSelectionStartX(GetSelectionEndX());
			SetSelectionEndX(matrix_temporary);
		}
		if (GetSelectionStartY() > GetSelectionEndY()) {
			matrix_temporary = GetSelectionStartY();
			SetSelectionStartY(GetSelectionEndY());
			SetSelectionEndY(matrix_temporary);
		}
		
		select_across1.RenderLine();
		select_across2.RenderLine();
		select_up1.RenderLine();
		select_up2.RenderLine();
		
		SetSelectedAreaSize();

		SetSelectedArea();
		
		select_started = false;
		select_finished = true;
		CopyMatrix();
	}
	else if (click_number == 2 && select_finished) {
		select_across1.RenderLine();
		select_across2.RenderLine();
		select_up1.RenderLine();
		select_up2.RenderLine();
	}
	else if (click_number == 3 && select_finished) {		
		select_finished = false;
	}
}

internal void
CopySelectedArea() {
	selected_area_copy = selected_area;
}

internal void
PasteSelectedArea() {

}

internal void
DeleteSelectedArea() {
	for (int i = GetSelectionStartX(); i < GetSelectionEndX(); i++) {
		for (int j = GetSelectionStartY(); j < GetSelectionEndY(); j++) {
			matrix[i][j] = 0xF1F1F1;
		}
	}
}

u32 original_x1;
u32 original_x2;
u32 original_y1;
u32 original_y2;

internal u32
GetOriginalX1() {
	return original_x1;
}
internal u32
GetOriginalX2() {
	return original_x2;
}
internal u32
GetOriginalY1() {
	return original_y1;
}
internal u32
GetOriginalY2() {
	return original_y2;
}
internal void
SetOriginalX1(u32 new_x1) {
	original_x1 = new_x1;
}
internal void
SetOriginalX2(u32 new_x2) {
	original_x2 = new_x2;
}
internal void
SetOriginalY1(u32 new_y1) {
	original_y1 = new_y1;
}
internal void
SetOriginalY2(u32 new_y2) {
	original_y2 = new_y2;
}

internal void
DeleteOriginalArea() {
	for (int i = GetOriginalX1(); i < GetOriginalX2(); i++) {
		for (int j = GetOriginalY1(); j < GetOriginalY2(); j++) {
			matrix[i][j] = 0xF1F1F1;
		}
	}
}

u32 click_number = 0;

internal void
SetClickNumber(u32 new_click_number) {
	click_number = new_click_number;
}
internal u32
GetClickNumber() {
	return click_number;
}

bool has_moved = false;

internal bool
GetMoveSelected() {
	return has_moved;
}
internal void
SetMoveSelected(bool now_is_moving) {
	has_moved = now_is_moving;
}

//End Matrix Functions//
//Show Cursor//

bool cursor_on_off;

internal void
SetCursorOn(bool value) {
	cursor_on_off = value;
}

internal bool
GetCursorOn() {
	return cursor_on_off;
}

//End Show Cursor//
//Accept and Store Text//
string text_input_box;

internal void
SetTextInput(string input) {
	text_input_box += input;
}

internal string
GetTextInput() {
	return text_input_box;
}

internal void
ClearTextInput() {
	text_input_box = "";
}

//End Accept and Store Text//
//Open or Close Save Input Menu//
bool save_menu_open;

internal bool
GetSaveMenuOpen() {
	return save_menu_open;
}

internal void
SetSaveMenuOpen(bool is_open) {
	save_menu_open = is_open;
}

//End Open or Close Save Input Menu//
//Open or Close Load Input Menu
bool load_menu_open;

internal bool
GetLoadMenuOpen() {
	return load_menu_open;
}

internal void
SetLoadMenuOpen(bool is_open) {
	load_menu_open = is_open;
}

//End Open or Close Save Input Menu//
//Open or Close Matrix Size Menu//
bool matrix_size_open;

internal bool
GetMatrixSizeOpen() {
	return matrix_size_open;
}

internal void
SetMatrixSizeOpen(bool is_open) {
	matrix_size_open = is_open;
}

//End Open or Close Matrix Size Menu//
//Open or Close Clear Confirmation//
bool clear_confirmation_is_open;

internal void
SetClearConfirmationOpen(bool is_open) {
	clear_confirmation_is_open = is_open;
}

internal bool
GetClearConfirmationOpen() {
	return clear_confirmation_is_open;
}
//End Clear Confirmation//
//Get and Set Colour Data to Load//
string save_data;

internal string
GetColourData() {
	return save_data;
}

internal void
SetColourData(string new_colour_data) {
	save_data = new_colour_data;
}

internal void
RemoveData(s32 index, s32 length) {
	string copy = save_data;
	copy.erase(index, length);
	save_data = copy;
}
internal void
RemoveExtraCharacters(char character) {
	string copy = save_data;
	copy.erase(character);
}

//End Colour Data Get and Set// 
//Open or Close Brush Size Menu//
bool brush_menu_open;

internal void
SetBrushSizeOpen(bool is_open) {
	brush_menu_open = is_open;
}

internal bool
GetBrushSizeOpen() {
	return brush_menu_open;
}

//End Open and Close of Brush Size Menu//
//Open or close the Selection Options//

bool selection_options_open = false;

internal void
SetSelectionOptionsOpen(bool is_open) {
	selection_options_open = is_open;
}
internal bool
GetSelectionOptionsOpen() {
	return selection_options_open;
}

//End Selection Options//
//Select Width or Height to Edit//
bool set_input_width;
bool set_input_height;

internal void
SetInputWidth(u32 new_width) {
	set_input_width = new_width;
}
internal bool
GetInputWidth() {
	return set_input_width;
}

internal void
SetInputHeight(u32 new_height) {
	set_input_height = new_height;
}
internal bool
GetInputHeight() {
	return set_input_height;
}