#define is_down(b) input->buttons[b].is_down
#define is_down(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

internal std::string
AcceptUserTextInput(Input* input) {
	if (is_down(BUTTON_A) && is_down(BUTTON_SHIFT)) {
		return ("A");
	}
	else if (is_down(BUTTON_A)) {
		return ("a");
	}

	if (is_down(BUTTON_B) && is_down(BUTTON_SHIFT)) {
		return ("B");
	}
	else if (is_down(BUTTON_B)) {
		return ("b");
	}

	if (is_down(BUTTON_C) && is_down(BUTTON_SHIFT)) {
		return ("C");
	}
	else if (is_down(BUTTON_C)) {
		return ("c");
	}

	if (is_down(BUTTON_D) && is_down(BUTTON_SHIFT)) {
		return ("D");
	}
	else if (is_down(BUTTON_D)) {
		return ("d");
	}

	if (is_down(BUTTON_E) && is_down(BUTTON_SHIFT)) {
		return ("E");
	}
	else if (is_down(BUTTON_E)) {
		return ("e");
	}

	if (is_down(BUTTON_F) && is_down(BUTTON_SHIFT)) {
		return ("F");
	}
	else if (is_down(BUTTON_F)) {
		return ("f");
	}

	if (is_down(BUTTON_G) && is_down(BUTTON_SHIFT)) {
		return ("G");
	}
	else if (is_down(BUTTON_G)) {
		return ("g");
	}

	if (is_down(BUTTON_H) && is_down(BUTTON_SHIFT)) {
		return ("H");
	}
	else if (is_down(BUTTON_H)) {
		return ("h");
	}

	if (is_down(BUTTON_I) && is_down(BUTTON_SHIFT)) {
		return ("I");
	}
	else if (is_down(BUTTON_I)) {
		return ("i");
	}

	if (is_down(BUTTON_J) && is_down(BUTTON_SHIFT)) {
		return ("J");
	}
	else if (is_down(BUTTON_J)) {
		return ("j");
	}

	if (is_down(BUTTON_K) && is_down(BUTTON_SHIFT)) {
		return ("K");
	}
	else if (is_down(BUTTON_K)) {
		return ("k");
	}

	if (is_down(BUTTON_L) && is_down(BUTTON_SHIFT)) {
		return ("L");
	}
	else if (is_down(BUTTON_L)) {
		return ("l");
	}

	if (is_down(BUTTON_M) && is_down(BUTTON_SHIFT)) {
		return ("M");
	}
	else if (is_down(BUTTON_M)) {
		return ("m");
	}

	if (is_down(BUTTON_N) && is_down(BUTTON_SHIFT)) {
		return ("N");
	}
	else if (is_down(BUTTON_N)) {
		return ("n");
	}

	if (is_down(BUTTON_O) && is_down(BUTTON_SHIFT)) {
		return ("O");
	}
	else if (is_down(BUTTON_O)) {
		return ("o");
	}

	if (is_down(BUTTON_P) && is_down(BUTTON_SHIFT)) {
		return ("P");
	}
	else if (is_down(BUTTON_P)) {
		return ("p");
	}

	if (is_down(BUTTON_Q) && is_down(BUTTON_SHIFT)) {
		return ("Q");
	}
	else if (is_down(BUTTON_Q)) {
		return ("q");
	}

	if (is_down(BUTTON_R) && is_down(BUTTON_SHIFT)) {
		return ("R");
	}
	else if (is_down(BUTTON_R)) {
		return ("r");
	}

	if (is_down(BUTTON_S) && is_down(BUTTON_SHIFT)) {
		return ("S");
	}
	else if (is_down(BUTTON_S)) {
		return ("s");
	}

	if (is_down(BUTTON_T) && is_down(BUTTON_SHIFT)) {
		return ("T");
	}
	else if (is_down(BUTTON_T)) {
		return ("t");
	}
	if (is_down(BUTTON_U) && is_down(BUTTON_SHIFT)) {
		return ("U");
	}
	else if (is_down(BUTTON_U)) {
		return ("u");
	}

	if (is_down(BUTTON_V) && is_down(BUTTON_SHIFT)) {
		return ("V");
	}
	else if (is_down(BUTTON_V)) {
		return ("v");
	}

	if (is_down(BUTTON_W) && is_down(BUTTON_SHIFT)) {
		return ("W");
	}
	else if (is_down(BUTTON_W)) {
		return ("w");
	}

	if (is_down(BUTTON_X) && is_down(BUTTON_SHIFT)) {
		return ("X");
	}
	else if (is_down(BUTTON_X)) {
		return ("x");
	}

	if (is_down(BUTTON_Y) && is_down(BUTTON_SHIFT)) {
		return ("Y");
	}
	else if (is_down(BUTTON_Y)) {
		return ("y");
	}

	if (is_down(BUTTON_Z) && is_down(BUTTON_SHIFT)) {
		return ("Z");
	}
	else if (is_down(BUTTON_Z)) {
		return ("z");
	}
}
