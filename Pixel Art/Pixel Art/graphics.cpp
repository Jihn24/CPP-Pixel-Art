#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

enum Mode {
	M_SELECT,
	M_PAINT,
};

u32 pixel_matrix[100][100];

internal bool
TwoDNearCollision(float p1x, float p1y, float half_size1, float p2x, float p2y, float half_size2) {
	if (p1x + half_size1 < p2x + half_size2 &&
		p1x - half_size1 > p2x - half_size2 &&
		p1y + half_size1 < p2y + half_size2 &&
		p1y - half_size1 > p2y - half_size2
		) return true;
	else return false;
}

internal void
RenderGraphics(int x, int y, float half_size_x, float half_size_y, u32 *colour) {
	DrawRect(x, y, half_size_x, half_size_y, *colour);
}

bool click_pressed;
bool selection_is_moving;
float pixel_size;
u32 drawing_offset_y;
u32 drawing_offset_x;
u32 colour;
u32 matrix_square_size;
bool is_tall;
bool is_wide;
bool is_square;

internal void 
SimulateGraphics(Input* input, float dt) {	
	matrix_square_size = max(GetMatrixWidth(), GetMatrixHeight());

	is_tall = false; is_wide = false; is_square = false;

	if (GetMatrixWidth < GetMatrixHeight) is_tall = true;
	else if (GetMatrixWidth > GetMatrixHeight) is_wide = true;
	else if (GetMatrixWidth == GetMatrixHeight) is_square = true;

	SetPixelSize(GetScreenWidth() / 2);
	SetPixelSize(GetPixelSize() / matrix_square_size);

	pixel_size = GetPixelSize();
	u32 x = GetCursorX();
	u32 y = GetCursorY();
			
	ClearScreen(110011);	

	RenderButtons();

	drawing_offset_y = 20;
	drawing_offset_x = (GetScreenWidth() - (GetMatrixWidth() * (pixel_size))) / 20;

	for (int i = 0; i <= matrix_square_size; i++) {
		for (int j = 0; j <= matrix_square_size; j++) {
			if (i < GetMatrixWidth() && j < GetMatrixHeight()) {
				colour = GetMatrix(i, j);
				float x = (drawing_offset_x + (pixel_size * i));
				float y = (drawing_offset_y + (pixel_size * j));
				RenderGraphics(x, y, ceil(pixel_size / 2), ceil(pixel_size / 2), &colour);
			}

		}
	}

	SetMatrixPositionX((x - drawing_offset_x) / (pixel_size));
	SetMatrixPositionY(y - drawing_offset_y);

	s32 matrix_position_x = GetMatrixPositionX();
	s32 matrix_position_y = GetMatrixPositionY();
	if (GetScreenHeight() > 700 || GetMatrixHeight() < 50)
		matrix_position_y = floor(matrix_position_y / pixel_size);
	else
		matrix_position_y = ceil(matrix_position_y / pixel_size);

	SetMatrixPositionX(matrix_position_x);
	SetMatrixPositionY(matrix_position_y);

	switch (paint_brush.GetBrushType()) {
	case 0: paint_brush.SetBoxColour(0x000000);  break;
	case 1: case 2: {
		if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
			if (matrix_position_x >= 0 && matrix_position_y >= 0 && matrix_position_x < matrix_square_size && matrix_position_y < matrix_square_size)
				SetMatrix(matrix_position_x, matrix_position_y, paint_brush.GetBoxColour(), paint_brush.GetBrushSize(), paint_brush.GetBrushType());
		}
		else if ((GetKeyState(VK_RBUTTON) & 0x8000) != 0) {
			if (matrix_position_x >= 0 && matrix_position_y >= 0 && matrix_position_x < GetMatrixWidth() && matrix_position_y <= GetMatrixHeight())
				SetMatrix(matrix_position_x, matrix_position_y, 0xF1F1F1, paint_brush.GetBrushSize(), paint_brush.GetBrushType());
		}
		break;
	}
	case 3: {
		if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
			if (!click_pressed) {
				if (matrix_position_x >= 0 && matrix_position_y >= 0 && matrix_position_x < GetMatrixWidth() && matrix_position_y < GetMatrixHeight() && click_number == 0 && !click_pressed) {
					click_number = 1;
					click_pressed = true;
				}	
				if (matrix_position_x >= 0 && matrix_position_y >= 0 && matrix_position_x < GetMatrixWidth() && matrix_position_y < GetMatrixHeight() && click_number == 1 && !click_pressed) {
					click_number = 2;
					click_pressed = true;
				}
			}
		}
		if ((GetKeyState(VK_LBUTTON) & 0x8000) == 0) click_pressed = false;		
		SetMatrixLine(matrix_position_x, matrix_position_y, paint_brush.GetBoxColour(), click_number);
		if (click_number == 2) click_number = 0;
		break;
	}
	case 4: {
		if (x > drawing_offset_x - 15 && y > drawing_offset_y - 15 && x < GetMatrixWidth() * ceil(pixel_size) + 3 && y < GetMatrixHeight() * ceil(pixel_size) + 3) {
			paint_brush.SetBoxColour(0x00FF00);
			if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0 && click_number == 0 && !click_pressed) {
				click_number = 1;
				click_pressed = true;
			}
			if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0 && click_number == 1 && !click_pressed) {
				click_number = 2;
				click_pressed = true;
				SetMenuOpen(true);
			}
		}
		else paint_brush.SetBoxColour(0xFF0000);
		if (click_number > 0) {
			MatrixSelection(matrix_position_x, matrix_position_y, click_number);
		}
		if (click_number == 2) {
			SetSelectionOptionsOpen(true);
			click_number = 3;
			paint_brush.SetBrushType(0); paint_brush.SetBrushSize(1);
		}
		if ((GetKeyState(VK_LBUTTON) & 0x8000) == 0) {
			click_pressed = false; 
		}
		break;
	}
	}

	//Draw Border//
	//Left
	DrawRect(drawing_offset_x - 2, drawing_offset_y, 1, GetMatrixHeight() * pixel_size / 2, 0x000000);
	//Right
	DrawRect(drawing_offset_x + GetMatrixWidth() * pixel_size, drawing_offset_y, 1, GetMatrixHeight() * pixel_size / 2, 0x000000);
	//Bottom
	DrawRect(drawing_offset_x - 2, drawing_offset_y, GetMatrixWidth() * pixel_size / 2 + 2, 1, 0x000000);
	//Top
	DrawRect(drawing_offset_x - 2, drawing_offset_y + GetMatrixHeight() * pixel_size, GetMatrixWidth() * pixel_size / 2 + 2, 1, 0x000000);
	//-----------//

	CreateTextInputs(input);
	CreateSliders();
	ConfirmationMenu();
	BrushMenu();

	//Create Paint Brush Last To Remain On Top//
	paint_brush.SetPosition_x(x); paint_brush.SetPosition_y(y);
	switch (paint_brush.GetBrushType()) {
	case 0: paint_brush.SetBrushSize(1); paint_brush.RenderBox(true); break;
	case 1: paint_brush.RenderBox(true); break;
	case 2: paint_brush.RenderCircle(true); break;
	case 3: paint_brush.RenderBox(true); break;
	case 4: paint_brush.RenderBox(true); break;
	}
	//------------------------//
}


