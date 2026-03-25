#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

internal void
RenderButtons() {	
	save_button.RenderBox(false);
	input_text_box.SetBoxText(input_text_box.GetInputText());

	int x = GetCursorX();
	int y = GetCursorY();

	if (save_button.ButtonSelected()) {
		SetSaveMenuOpen(true);
		SetSaveAll(true);
		paint_brush.StoreBrush();
		paint_brush.SetBrushType(0);
	}

	load_button.RenderBox(false);
	
	if (load_button.ButtonSelected()) {
		SetLoadMenuOpen(true);
		paint_brush.StoreBrush();
		paint_brush.SetBrushType(0);
	}

	change_size_button.RenderBox(false);

	if (change_size_button.ButtonSelected()) {
		SetMatrixSizeOpen(true);
		paint_brush.StoreBrush();
		paint_brush.SetBrushType(0);
	}	

	brush_button.RenderBox(false);

	if (brush_button.ButtonSelected()) {
		SetBrushSizeOpen(true);
	}

	clear_canvas_button.RenderBox(false);

	if (clear_canvas_button.ButtonSelected()) {
		SetClearConfirmationOpen(true);
		paint_brush.StoreBrush();
		paint_brush.SetBrushType(0);
	}

	change_background_button.RenderBox(false);

	if (change_background_button.ButtonSelected()) {
		for (int i = 0; i < GetMatrixWidth(); i++) {
			for (int j = 0; j < GetMatrixHeight(); j++) {
				if (matrix[i][j] == 0xF1F1F1) {
					matrix[i][j] = paint_brush.GetBoxColour();
				}
			}
		}
	}

	int index = 0;

	for (int i = 0; i < 10; i++) {	

		if (user_colour_buttons[i].ButtonSelected()) paint_brush.SetBoxColour(user_colour_buttons[i].GetBoxColour());
		if (user_colour_buttons[i].ButtonRightClicked()) user_colour_buttons[i].SetBoxColour(paint_brush.GetBoxColour());
		user_colour_buttons[i].RenderBox(false);

		for (int j = 0; j < 10; j++) {
			Button button = GetButton(index);
			button.RenderBox(false);
			if (button.ButtonSelected()) {
				paint_brush.SetBoxColour(button.GetBoxColour());
			}		
			index++;	
		} 		
	}
}

string save_name;

internal void
CreateTextInputs(Input* input) {
	//Render Input Save Name Menu//
	int x = GetCursorX();
	int y = GetCursorY();
	if (GetSaveMenuOpen()) {
		SetMatrixSizeOpen(false);
		SetLoadMenuOpen(false);
		SetBrushSizeOpen(false);
		SetClearConfirmationOpen(false);

		SimulateTextInputs(input, input_text_box);
		input_text_box.SetDescription("save name");
		input_text_box.UpdateText();
		input_text_box.RenderBox(false);
	

		close_input_button.RenderBox(false);

		if (close_input_button.ButtonSelected()) {
			input_text_box.ClearText();
			paint_brush.RestoreBrush();
			SetSaveMenuOpen(false);
		}

		input_button.RenderBox(false);

		if (input_button.ButtonSelected()) {
			string save_name_new_string = input_text_box.GetBoxText()[1];
			save_name = "..\\Save_Files\\" + save_name_new_string + ".txt";
			file_exists = GetFileAttributes(save);
			SetSaveMenuOpen(false);
			SetSaveConfirmationOpen(true);
			input_text_box.ClearText();						
		}

		if (load_button.ButtonSelected()) {
			SetSaveMenuOpen(false);
			SetLoadMenuOpen(true);
		}
		if (change_size_button.ButtonSelected()) {
			SetSaveMenuOpen(false);
			SetMatrixSizeOpen(true);
		}
		if (brush_button.ButtonSelected()) {
			SetSaveMenuOpen(false);
			SetBrushSizeOpen(true);
		}
		if (clear_canvas_button.ButtonSelected()) {
			SetSaveMenuOpen(false);
			SetClearConfirmationOpen(true);
		}
	}
	//------------------------//
	//Render Input Load Name Menu//

	string load_name;

	if (GetLoadMenuOpen()) {
		SetMatrixSizeOpen(false);
		SetSaveMenuOpen(false);
		SetBrushSizeOpen(false);
		SetClearConfirmationOpen(false);

		SimulateTextInputs(input, input_text_box);
		input_text_box.SetDescription("load name");
		input_text_box.UpdateText();
		input_text_box.RenderBox(false);
		

		close_input_button.RenderBox(false);

		if (close_input_button.ButtonSelected()) {
			input_text_box.ClearText();
			paint_brush.RestoreBrush();

			SetLoadMenuOpen(false);
		}

		input_button.RenderBox(false);

		if (input_button.ButtonSelected()) {
			string save_name_new_string = input_text_box.GetBoxText()[1];
			load_name = "..\\Save_Files\\" + save_name_new_string + ".txt";
			LoadMatrix(load_name);
			input_text_box.ClearText();
			paint_brush.RestoreBrush();

			SetLoadMenuOpen(false);
		}

		if (save_button.ButtonSelected()) {
			SetLoadMenuOpen(false);
			SetSaveMenuOpen(true);
		}
		if (change_size_button.ButtonSelected()) {
			SetLoadMenuOpen(false);
			SetMatrixSizeOpen(true);			
		}
		if (brush_button.ButtonSelected()) {
			SetLoadMenuOpen(false);
			SetBrushSizeOpen(true);
		}
		if (clear_canvas_button.ButtonSelected()) {
			SetLoadMenuOpen(false);
			SetClearConfirmationOpen(true);
		}
	}
	//------------------------//
	//Render Matrix Size Menu//

	string matrix_size_string;
	u32 new_matrix_width;
	u32 new_matrix_height;
	bool only_numbers;

	if (GetMatrixSizeOpen()) {
		SetLoadMenuOpen(false);
		SetSaveMenuOpen(false);
		SetBrushSizeOpen(false);
		SetClearConfirmationOpen(false);
		
		width_text_box.RenderBox(false);
		height_text_box.RenderBox(false);
		width_label.RenderBox(false);
		height_label.RenderBox(false);
		width_x_height.RenderBox(false);
		
		if (width_text_box.ButtonSelected()) {
			SetInputWidth(true);
			SetInputHeight(false);
		}			
		
		if (height_text_box.ButtonSelected()) {
			SetInputHeight(true);
			SetInputWidth(false);
		}
		
		if (GetInputWidth()) {
			SimulateTextInputs(input, width_text_box);
		}
		if (GetInputHeight()) {
			SimulateTextInputs(input, height_text_box);
		}	

		width_text_box.UpdateText();
		height_text_box.UpdateText();

		close_input_button.RenderBox(false);

		if (close_input_button.ButtonSelected()) {
			width_text_box.ClearText();
			height_text_box.ClearText();
			paint_brush.RestoreBrush();

			SetMatrixSizeOpen(false);
		}

		input_button.RenderBox(false);

		if (input_button.ButtonSelected()) {
			string matrix_new_width = width_text_box.GetBoxText()[0];
			string matrix_new_height = height_text_box.GetBoxText()[0];
			only_numbers = true;

			for (int i = 0; i < matrix_new_width.size(); i++) {
				const char* character = find(begin(numbers), end(numbers), matrix_new_width[i]);
				if (character == end(numbers)) {
					only_numbers = false;
				}
			}

			for (int i = 0; i < matrix_new_height.size(); i++) {
				const char* character = find(begin(numbers), end(numbers), matrix_new_height[i]);
				if (character == end(numbers)) {
					only_numbers = false;
				}
			}

			if (only_numbers) {
				new_matrix_width = stoi(matrix_new_width);
				new_matrix_height = stoi(matrix_new_height);

				DeleteFile("..\\resize_temp_file.txt");
				SaveMatrix("..\\resize_temp_file.txt");
				SetMatrixSize(new_matrix_width, new_matrix_height);
				LoadMatrix("..\\resize_temp_file.txt");
			}

			width_text_box.ClearText();
			height_text_box.ClearText();
			paint_brush.RestoreBrush();

			SetMatrixSizeOpen(false);
		}

		if (save_button.ButtonSelected()) {
			SetMatrixSizeOpen(false);
			SetSaveMenuOpen(true);
		}
		if (load_button.ButtonSelected()) {
			SetMatrixSizeOpen(false);
			SetLoadMenuOpen(true);
		}
		if (brush_button.ButtonSelected()) {
			SetMatrixSizeOpen(false);
			SetBrushSizeOpen(true);
		}
		if (clear_canvas_button.ButtonSelected()) {
			SetMatrixSizeOpen(false);
			SetClearConfirmationOpen(true);
		}
	}
	//------------------------//
	//Render Selection Options//
	if (GetSelectionOptionsOpen()) {
		if (!GetMoveSelected() && move_selected.CentredButtonSelected()) {
			DeleteOriginalArea();
			CopyMatrix();
			SetMoveSelected(true);
		}
		if (!move_selected.CentredButtonSelected()) {
			SetSelectionOptionsPosition();
			SetSelectedArea();
			SetOriginalX1(GetSelectionStartX());
			SetOriginalX2(GetSelectionEndX());
			SetOriginalY1(GetSelectionStartY());
			SetOriginalY2(GetSelectionEndY());
			SetMoveSelected(false);
		}
		RenderSelectionBox();
		RenderSelectionOptions();			
		if (move_selected.CentredButtonSelected()) {
			SetWholeMatrix(GetCopyMatrix());
			
			SetSelectionX1(GetCursorX());
			SetSelectionX2(GetCursorX() + GetCoordinateWidth());
			SetSelectionY1(GetCursorY());
			SetSelectionY2(GetCursorY() + GetCoordinateHeight());
			SetSelectionStartX(GetMatrixPositionX());
			SetSelectionEndX(GetMatrixPositionX() + GetSelectedAreaWidth());
			SetSelectionStartY(GetMatrixPositionY());
			SetSelectionEndY(GetMatrixPositionY() + GetSelectedAreaHeight());
			select_across1.CreateLineByPoints(select_x1, select_y1, select_x2, select_y1, 2, 0x000000);
			select_across2.CreateLineByPoints(select_x1, select_y2, select_x2, select_y2, 2, 0x000000);
			select_up1.CreateLineByPoints(select_x1, select_y1, select_x1, select_y2, 2, 0x000000);
			select_up2.CreateLineByPoints(select_x2, select_y1, select_x2, select_y2, 2, 0x000000);
			
			SetMatrixToSelected(GetMatrixPositionX(), GetMatrixPositionY());
			SetMoveSelected(true);
		}		
		if (copy_selected.ButtonSelected()) {
			CopySelectedArea();
		}
		if (delete_selected.ButtonSelected()) {
			DeleteSelectedArea();
		}
		if (save_selected.ButtonSelected()) {
			SetSaveAll(false);
			SetSaveMenuOpen(true);
		}
		
		if (close_selected.CentredButtonSelected()) {
			SetClickNumber(0);
			paint_brush.RestoreBrush();

			SetMoveSelected(false);
			SetSelectionOptionsOpen(false);
		}
	}
	//------------------------//

}

float red_value;
string red_hex_value;
float green_value;
string green_hex_value;
float blue_value;
string blue_hex_value;

string new_colour_box_hex;
u32 new_colour_box_int;

internal void
CreateSliders() {
	int x = GetCursorX();
	int y = GetCursorY();

	red_slider.RenderBox(false);
	red_slider.RenderSlider();

	if (red_slider.ButtonSelected()) {
		red_slider.SetSliderPosition_x(x);
	}
	red_value = (red_slider.GetSliderPosition_x() - red_slider.GetPosition_x()) * (257.f / red_slider.GetWidth());
	red_hex_value = DecToHex(red_value);
	if (red_hex_value == "000000") {
		red_hex_value = "00";
	}
	if (red_hex_value.size() < 2) {
		red_hex_value = "0" + red_hex_value;
	}

	green_slider.RenderBox(false);
	green_slider.RenderSlider();

	if (green_slider.ButtonSelected()) {
		green_slider.SetSliderPosition_x(x);
	}
	green_value = (green_slider.GetSliderPosition_x() - green_slider.GetPosition_x()) * (257.f / green_slider.GetWidth());
	green_hex_value = DecToHex(green_value);
	if (green_hex_value == "000000") {
		green_hex_value = "00";
	}
	if (green_hex_value.size() < 2) {
		green_hex_value = "0" + green_hex_value;
	}

	blue_slider.RenderBox(false);
	blue_slider.RenderSlider();

	if (blue_slider.ButtonSelected()) {
		blue_slider.SetSliderPosition_x(x);
	}
	blue_value = (blue_slider.GetSliderPosition_x() - blue_slider.GetPosition_x()) * (257.f / blue_slider.GetWidth());
	blue_hex_value = DecToHex(blue_value);
	if (blue_hex_value == "000000") {
		blue_hex_value = "00";
	}
	if (blue_hex_value.size() < 2) {
		blue_hex_value = "0" + blue_hex_value;
	}

	new_colour_box_hex = "0x" + red_hex_value + green_hex_value + blue_hex_value;
	new_colour_box_int = stoi(new_colour_box_hex, 0, 16);
	
	new_colour_box.SetBoxColour(new_colour_box_int);
	new_colour_box.RenderBox(false);

	if (new_colour_box.ButtonSelected()) {
		paint_brush.SetBoxColour(new_colour_box.GetBoxColour());
	}
}

internal void
BrushMenu() {
	int x = GetCursorX();
	int y = GetCursorY();

	if (GetBrushSizeOpen()) {
		small_brush.RenderCircle(true);
		medium_circle_brush.RenderCircle(true);
		large_circle_brush.RenderCircle(true);
		medium_square_brush.RenderBox(true);
		large_square_brush.RenderBox(true);
		straight_line_tool.RenderBox(true);
		select_tool.RenderBox(true);

		if (small_brush.CentredButtonSelected()) {
			paint_brush.SetBrushSize(1);
			paint_brush.SetBrushType(2);
			paint_brush.StoreBrush();
		}
		if (medium_circle_brush.CentredButtonSelected()) {
			paint_brush.SetBrushSize(2);
			paint_brush.SetBrushType(2);
			paint_brush.StoreBrush();
		}
		if (large_circle_brush.CentredButtonSelected()) {
			paint_brush.SetBrushSize(3);
			paint_brush.SetBrushType(2);
			paint_brush.StoreBrush();
		}
		if (medium_square_brush.CentredButtonSelected()) {
			paint_brush.SetBrushSize(2);
			paint_brush.SetBrushType(1);
			paint_brush.StoreBrush();
		}
		if (large_square_brush.CentredButtonSelected()) {
			paint_brush.SetBrushSize(3);
			paint_brush.SetBrushType(1);
			paint_brush.StoreBrush();
		}
		if (straight_line_tool.CentredButtonSelected()) {
			paint_brush.SetBrushSize(1);
			paint_brush.SetBrushType(3);
			paint_brush.StoreBrush();
		}
		if (select_tool.CentredButtonSelected()) {
			paint_brush.SetBrushSize(1);
			paint_brush.SetBrushType(4);
			paint_brush.StoreBrush();
		}

		if (save_button.ButtonSelected()) {
			SetBrushSizeOpen(false);
			SetSaveMenuOpen(true);
		}
		if (load_button.ButtonSelected()) {
			SetBrushSizeOpen(false);
			SetLoadMenuOpen(true);
		}
		if (change_size_button.ButtonSelected()) {
			SetBrushSizeOpen(false);
			SetMatrixSizeOpen(true);
		}
	}
}


internal void
ConfirmationMenu() {
	int x = GetCursorX();
	int y = GetCursorY();

	if (GetSaveConfirmationOpen()) {
		confirmation_box.AddBoxText({ "Overwrite", "Save File?" }, 0x000000, 4, "CENTRE", 10, "CENTRE", 10);
		confirmation_box.RenderBox(false);
		reject.RenderBox(false);
		confirm.RenderBox(false);

		if (confirm.ButtonSelected()) {
			DeleteFile(save_name.c_str());
			if (GetSaveAll()) SaveMatrix(save_name);
			if (!GetSaveAll()) {
				SetMenuOpen(false);
				SaveSelectedArea(save_name);
			}
			paint_brush.RestoreBrush();

			SetSaveConfirmationOpen(false);
		}
		if (reject.ButtonSelected()) {
			paint_brush.RestoreBrush();

			SetSaveConfirmationOpen(false);
		}
	}

	if (GetClearConfirmationOpen()) {
		confirmation_box.AddBoxText({ "Clear Screen?" }, 0x000000, 4, "CENTRE", 10, "CENTRE", 10);
		confirmation_box.RenderBox(false);
		reject.RenderBox(false);
		confirm.RenderBox(false);

		if (confirm.ButtonSelected()) {
			ClearMatrix();
			paint_brush.RestoreBrush();

			SetClearConfirmationOpen(false);
		}
		if (reject.ButtonSelected()) {
			paint_brush.RestoreBrush();

			SetClearConfirmationOpen(false);
		}
	}
}
