#import <AppKit/NSScreen.h>

void	mlx_get_screen_size(void *mlx_ptr, int *width, int *height)
{
	(void)mlx_ptr;
	NSRect disp = [[NSScreen mainScreen] frame];
	*height = (int)disp.size.height;
	*width = (int)disp.size.width;
}
