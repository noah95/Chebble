#include <pebble.h>

Window *window;
TextLayer *text_layer;
TextLayer *hide_cheat_layer;

// This is a scroll layer
static ScrollLayer *scroll_layer;

// Lorem ipsum to have something to scroll
static char cheat_text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam quam tellus, fermentu  m quis vulputate quis, vestibulum interdum sapien. Vestibulum lobortis pellentesque pretium. Quisque ultricies purus e  u orci convallis lacinia. Cras a urna mi. Donec convallis ante id dui dapibus nec ullamcorper erat egestas. Aenean a m  auris a sapien commodo lacinia. Sed posuere mi vel risus congue ornare. Curabitur leo nisi, euismod ut pellentesque se  d, suscipit sit amet lorem. Aliquam eget sem vitae sem aliquam ornare. In sem sapien, imperdiet eget pharetra a, lacin  ia ac justo. Suspendisse at ante nec felis facilisis eleifend.";
static char hide_text[] = "Hidden!";

static const int vert_scroll_text_padding = 20;  //space on the bottom of the text layer when scrolling all way down

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  
  //layer_add_child(window_layer, hide_cheat_layer);
}

static void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  
  //text_layer_destroy(hide_cheat_layer);
}





// Setup the scroll layer on window load
// We do this here in order to be able to get the max used text size
static void window_load(Window *window) {
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = GRect(0, 0, 144, 168); //full screen
  GRect max_text_bounds = GRect(0, 0, bounds.size.w, 2000);
  
  /******************* init hide layer ***********************/
  hide_cheat_layer = text_layer_create(bounds);
  hide_cheat_layer = text_layer_create(max_text_bounds);
  text_layer_set_background_color(hide_cheat_layer, GColorBlack);
  text_layer_set_text_color(hide_cheat_layer, GColorWhite);
  text_layer_set_font(hide_cheat_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(hide_cheat_layer, hide_text);
  
  
  /******************* init text layer ***********************/
  text_layer = text_layer_create(bounds);
  text_layer = text_layer_create(max_text_bounds);
  text_layer_set_background_color(text_layer, GColorBlack);
  text_layer_set_text_color(text_layer, GColorWhite);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(text_layer, cheat_text);
  
  
  /******************* Initialize the scroll layer ***********************/
  scroll_layer = scroll_layer_create(bounds);
  
  // This binds the scroll layer to the window so that up and down map to scrolling
  // may use scroll_layer_set_callbacks to add or override interactivity
  scroll_layer_set_click_config_onto_window(scroll_layer, window);

  // Trim text layer and scroll content to fit text box
  GSize max_size = text_layer_get_content_size(text_layer);
  scroll_layer_set_content_size(scroll_layer, GSize(bounds.size.w, max_size.h + vert_scroll_text_padding));
  
  //hide the top and bottom scroll border for more text view
  scroll_layer_set_shadow_hidden(scroll_layer, true);
  
  // Add the layers for display
  scroll_layer_add_child(scroll_layer, text_layer_get_layer(text_layer));
  
	//layer_add_child(window_layer, text_layer_get_layer(text_layer));
  layer_add_child(window_layer, scroll_layer_get_layer(scroll_layer));
}

static void window_unload(Window *window) {
  //inverter_layer_destroy(inverter_layer);
  text_layer_destroy(text_layer);
  scroll_layer_destroy(scroll_layer);
}

void handle_init(void) {
  /*
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 168));
	
  //disable status bar
  window_set_fullscreen(window, true);
  
	// Set the text, font, and text alignment
  text_layer_set_background_color(text_layer, GColorBlack);
  text_layer_set_text_color(text_layer, GColorWhite);
	text_layer_set_text(text_layer, "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
	
  
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
*/
  
  
  window = window_create();
  
  //disable status bar
  window_set_fullscreen(window, true);
  
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true /* Animated */);
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
  window_destroy(window);
}
