#include "so_long.h"

int		main(void)
{
	all_mallocs	*stuff_to_free;
	stuff_to_free = malloc(sizeof(all_mallocs));						// ‼️‼️ Use free or free function
	if(!stuff_to_free)
	{
		return(1);
	}
// ----------------------------------------------------------------------------------------------------- Game checklist - Create a window for the game ✅Ⓜ️🆓
	mlx_t	*game_window;
	if(!(game_window = mlx_init(500, 500, "Step 1 - Done !", false)))	// If connection to the graphical system set up fails - MLX MALLOC DONE HERE ‼️
	{
		ft_printf("Error in the window allocation\n");
		return(1);
		/* Autre option : ecrire juste une ligne ft_error();	puis creer cette fonction qui utilise exit (a etudier) : https://github.com/codam-coding-college/MLX42/blob/master/docs/Images.md */
	}
	stuff_to_free->window =			game_window;

	/* If needed : Add the others in .h struct + here */
// ------------------------------------------------------------------ Set up Texture buffer (texture = Image pas encore affichée, mais prête à l’être) ✅Ⓜ️🆓
	mlx_texture_t *player_texture;
	if (!(player_texture = mlx_load_png("/home/schappuy/00_VS_Code/4_So_Long/ic_Play.png")))	// Access the image data - MLX MALLOC DONE HERE ‼️
	{
		ft_printf("Failed to load PNG into texture\n");
		mlx_terminate(game_window);	// Destroy and clean up all images and mlx resources.
		return (1);
	}
	stuff_to_free->player_texture =	player_texture;

// --------------------------------------------------------------------------------------------------------- Convert the texture to a diplayable image ✅Ⓜ️🆓
	mlx_image_t *player_image;															// Set up image buffer - Note : mlx_image_t doit etre toujours un ptr
	if (!(player_image = mlx_texture_to_image(game_window, player_texture)))			// Create a displayable image from texture data - MLX MALLOC DONE HERE ‼️
	{
		ft_printf("Error in allocating new image buffer\n");
		mlx_terminate(game_window);	// Destroy and clean up all images and mlx resources.
		return (1);
	}
	stuff_to_free->player_image =	player_image;

// --------------------------------------------------------------------------------------------------------------------------------- Display the image ✅
	if (mlx_image_to_window(game_window, player_image, 0, 0) == -1)	// Affiche une instance de l'image. Peut être utilisé à chaque fois qu'on veut display l'image à un endroit différent
	{
		ft_printf("Erreur lors de l'affichage de l'image\n");
		ft_free_exit(stuff_to_free);
		return (1);
	}
// ------------------------------------------------------------ Game checklist - Create the required structure to store all the necessary information ❓❔
// ---------------------------------------------- Game checklist - Load all the required sprites (image data) for your game and store them into memory ‼️✅Ⓜ️🆓
	mlx_texture_t *collec_texture;
	collec_texture = ft_check_texture(stuff_to_free, "/home/schappuy/00_VS_Code/4_So_Long/ic_Coll.png");	// Access the image data - MLX MALLOC DONE HERE ‼️
	if (!collec_texture)
		return(1);
	stuff_to_free->collec_texture =	collec_texture;

	mlx_texture_t *exit_texture;
	exit_texture = ft_check_texture(stuff_to_free, "/home/schappuy/00_VS_Code/4_So_Long/ic_Exit.png");	// MLX MALLOC DONE HERE ‼️
	if (!exit_texture)
		return(1);
	stuff_to_free->exit_texture =	exit_texture;

	mlx_texture_t *ground_texture;
	ground_texture = ft_check_texture(stuff_to_free, "/home/schappuy/00_VS_Code/4_So_Long/ic_Grou.png");	// MLX MALLOC DONE HERE ‼️
	if (!ground_texture)
		return(1);
	stuff_to_free->ground_texture =	ground_texture;

	mlx_texture_t *wall_texture;
	wall_texture = ft_check_texture(stuff_to_free, "/home/schappuy/00_VS_Code/4_So_Long/ic_Wall.png");	// MLX MALLOC DONE HERE ‼️
	if(!wall_texture)
		return(1);
	stuff_to_free->wall_texture =	wall_texture;

// ------------------------------------------------------------------------------------------------------ Game checklist - Create the different hooks ‼️
/* Hooks allow you to add your own functions to the main loop execution of the program, aka these functions get executed every frame.
They also serve to intercept certain keypresses such as scrolling or pressing enter.
Only one hook can be set at a time! You cannot attach/have multiple specialized hooks. You can however have multiple generic hooks. */

	mlx_key_hook(game_window, ft_key_move, stuff_to_free);

/* Notes random
🟡 Callback function = Use the amound of parameters mentionned in the .h - If need more, use struct
🟠 MLX42 ne supporte qu’un seul mlx_key_hook() à la fois. ✅ Solution : tout gérer dans une seule fonction de hook.
🟡 image->instances[0].x/y = Déplacer une image
🟣 mlx_image_t *img = mlx_new_image(mlx, 32, 32);		= Créer une image à partir de zéro
🟣 mlx_image_t *img = mlx_texture_to_image(mlx, tex);	= Créer une image à partir d’une texture existante
🔵 Ne free() jamais ce que MLX a donné
🔵 mlx_terminate() s’occupe de free tout ce qui vient de MLX
🟢 mlx_key_hook() déclenche une action quand une touche est pressée ou relâchée.
	mlx_key_hook() appelle ma fonction ft_key_move (faite sur la base d'une callback function : mlx_keyfun) chaque fois qu’une touche est pressée.
	game_window = la fenêtre qui gère les touches
	ft_key_move = la fonction à appeler à chaque touche pressée
	player_image = donnée qu’on te renverra en param → c’est ce qu’on va déplacer
*/


	mlx_close_hook(game_window, ft_clic_exit, stuff_to_free);

// --------------------------------------------------------------------------------------------------------------------- Game checklist - key_handler ‼️
// ---------------------------------------------------------------------------------------------------- Game checklist - mouse_handler (if necessary) ‼️
// ------------------------------------------------ Game checklist - close_handler, this is a hook on the red cross that closes the program correctly ‼️
// ---------------------------------------------------------------------------------------------------- Game checklist - loop_hook (=> you game loop) ‼️
// ----------------------------------------------------------------------------------------------------------- Render checklist - Draw the background ‼️
// ----------------------------------------------------------------------------------------- Render checklist - Draw the not movable parts of the map ‼️
// --------------------------------------------------------------------------------------------------------------- Render checklist - Draw the player ‼️

	mlx_loop(game_window);					// ‼️Keep at the end - Starts to render to window with all requested elements, until shutdown is not requested (zb: closing the window)
	ft_free_exit(stuff_to_free);			// In case ESC pressed or if everything goes correctly and the exit is naturally happening when all collectibles are reached ?

 // ‼️ Trouver un moyen pour que ça n'accepte que les .ber
	int size_path = ft_strlen(PATH);									// ‼️ Check if mallocs done
	char *extension = ft_substr(PATH, (size_path - 4), size_path);		// ‼️ Check if mallocs done

	if (ft_strncmp (extension, ft_strdup(".txt"), 5) != 0)				// ‼️ Check if mallocs done + Remplacer par .ber
		return (1);

	int	fd;
	fd = open(PATH, O_RDWR);

	if((!fd) || (fd < 0))
	{
		ft_printf ("Error\n>> Map missing OLALA NICHT GUT\n\n");
		return (1);
	}
	so_long(fd);
	return (0);
}
