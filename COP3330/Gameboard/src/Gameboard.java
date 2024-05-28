import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;

public class Gameboard extends JPanel implements Serializable {
 private Cell[][] cells;
 private JPanel[][] panels;
 private Gameboard currentGameboard;
 private byte[] obstacleImage1Bytes;
 private byte[] obstacleImage2Bytes;
 private byte[] wallImageBytes;
 private byte[] rewardImage1Bytes;
 private byte[] rewardImage2Bytes;
 private byte[] rewardImage3Bytes;
 private byte[] exitSignBytes;
 private byte[] entranceSignBytes;

 private static final long serialVersionUID = 1L;

 private int entrance, exit;
 private BufferedImage obstacleImage1, obstacleImage2, rewardImage1, rewardImage2, rewardImage3, exitSign, entranceSign, wallImage;

 public Gameboard() {
    // this.setTitle("Board Game");
     this.setSize(320, 320); // 32x32 cells * 10 pixels each
    // this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

     try {
         obstacleImage1 = ImageIO.read(new File("img/spider rider.png"));
         obstacleImage2 = ImageIO.read(new File("img/creeper.png"));
         rewardImage1 = ImageIO.read(new File("img/expminecraft.png"));
         rewardImage2 = ImageIO.read(new File("img/diamond reward.png"));
         rewardImage3 = ImageIO.read(new File("img/apple minecraft.png"));
         wallImage = ImageIO.read(new File("img/Cobblestone.png"));

     } catch (IOException e) {
         e.printStackTrace();
     }
     try {
         obstacleImage1Bytes = convertImageToBytes(obstacleImage1);
         obstacleImage2Bytes = convertImageToBytes(obstacleImage2);
         rewardImage1Bytes = convertImageToBytes(rewardImage1);
         rewardImage2Bytes = convertImageToBytes(rewardImage2);
         rewardImage3Bytes = convertImageToBytes(rewardImage3);
         wallImageBytes = convertImageToBytes(wallImage);
     } catch (IOException e) {
         e.printStackTrace();
     }

     cells = new Cell[32][32];
     for (int i = 0; i < 32; i++) {
         for (int j = 0; j < 32; j++) {
             cells[i][j] = new Cell();
             //cells[i][j].setImage(obstacleImage1);
         }
     }

     Random random = new Random();

  // Generate a random number for the entrance in the top row (excluding the outside walls)
  entrance = random.nextInt(30) + 1; // This will generate a random number between 1 and 30

  // Generate a random number for the exit in the bottom row (excluding the outside walls)
  exit = random.nextInt(30)+1; // This will generate a random number between 961 and 990

  cells[0][entrance].setImage(entranceSign); // Top
  cells[31][exit].setImage(exitSign); // Bottom
  Wall wall = new Wall(wallImage);

//Assign the walls to the cells in the top row, leftmost column, rightmost column, and bottom row
  for (int i = 0; i < 32; i++) {
      if (i != entrance) {
          cells[0][i].setObject(wall, 1); // Top
      }
      if (i != exit) {
          cells[31][i].setObject(wall, 4); // Bottom
      }
  }

  for (int i = 0; i < 32; i++) {
      cells[i][0].setObject(wall, 2); // Left
      cells[i][31].setObject(wall, 3); // Right
  }

  Set<String> usedPositions = new HashSet<>();

  for (int i = 0; i < 256; i++) {
     int x, y, position;
     do {
         x = random.nextInt(32);
         y = random.nextInt(32);
         position = random.nextInt(3) + 1; // Randomly choose a position ( top, left, right, bottom)
     } while (usedPositions.contains(x + "," + y ));

     cells[x][y].setObject(wall, position);
     usedPositions.add(x + "," + y );
  }

     Obstacle[] spider = new Obstacle[16];
     for (int i = 0; i < 16; i++) {
    	 spider[i] = new Obstacle();
    	 spider[i].setImage(obstacleImage1);
         placeObstacle(spider[i], randomPosition());
     }
     Obstacle[] creeper = new Obstacle[16];
     for (int i = 0; i < 16; i++) {
    	 creeper[i] = new Obstacle();
    	 creeper[i].setImage(obstacleImage2);
         placeObstacle(creeper[i], randomPosition());
     }

     Reward[] diamond = new Reward[16];
     for (int i = 0; i < 16; i++) {
    	 diamond[i] = new Reward();
    	 diamond[i].setImage(rewardImage1);
         placeReward(diamond[i], randomPosition());

     }
     Reward[] apple = new Reward[16];
     for (int i = 0; i < 16; i++) {
    	 apple[i] = new Reward();
    	 apple[i].setImage(rewardImage2);
         placeReward(apple[i], randomPosition());

     }
     Reward[] experience = new Reward[16];
     for (int i = 0; i < 16; i++) {
    	 experience[i] = new Reward();
    	 experience[i].setImage(rewardImage3);
         placeReward(experience[i], randomPosition());

     }
     panels = new JPanel[32][32];

  // Inside the constructor after creating panels[i][j]:
  // Add the panels to the content pane with a GridLayout
  setLayout(new GridLayout(32, 32));
  for (int i = 0; i < 32; i++) {
      for (int j = 0; j < 32; j++) {
          final int x = i; 
          final int y = j; 

          panels[i][j] = new JPanel() {
   
			private static final long serialVersionUID = 1L;

			// ...
             @Override
             protected void paintComponent(Graphics g) {
                 super.paintComponent(g);
                 Graphics2D g2d = (Graphics2D) g;
                 g2d.setColor(Color.GRAY);
                 g2d.fillRect(0, 0, getWidth(), getHeight());
                 if (cells[x][y].getObject(0) != null) {
                     g2d.drawImage(cells[x][y].getObject(0).getImage(), 0, 0, getWidth(), getHeight(), this);
                 }
                 if (cells[x][y].getObject(1) != null) {
                     g2d.drawImage(cells[x][y].getObject(1).getImage(), 0, 0, getWidth(), getHeight() / 3, this);
                 }
                 if (cells[x][y].getObject(2) != null) {
                     g2d.drawImage(cells[x][y].getObject(2).getImage(), 0, 0, getWidth() / 4, getHeight(), this);
                 }
                 if (cells[x][y].getObject(3) != null) {
                     g2d.drawImage(cells[x][y].getObject(3).getImage(), getWidth()-getWidth() / 4, 0, getWidth() / 4, getHeight(), this);
                 }
                 if (cells[x][y].getObject(4) != null) {
                     g2d.drawImage(cells[x][y].getObject(4).getImage(), 0, getHeight() -getHeight()/3, getWidth(), getHeight() / 3, this);
                 }
             }
          };

          panels[i][j].setPreferredSize(new Dimension(10, 10));
          panels[i][j].setBackground(Color.GRAY);

          this.add(panels[i][j]);
      }
  }




 }
 
 private byte[] convertImageToBytes(BufferedImage image) throws IOException {
     ByteArrayOutputStream baos = new ByteArrayOutputStream();
     ImageIO.write(image, "png", baos);
     return baos.toByteArray();
 }
 private BufferedImage convertBytesToImage(byte[] imageBytes) throws IOException {
     ByteArrayInputStream bais = new ByteArrayInputStream(imageBytes);
     return ImageIO.read(bais);
 }
 
 private void placeObstacle(Obstacle obstacle, int position) {
	  int x = position / 32;
	  int y = position % 32;
	  cells[x][y].setObject(obstacle,0);
	}

	private void placeReward(Reward reward, int position) {
	  int x = position / 32;
	  int y = position % 32;
	  cells[x][y].setReward(reward);
	}

 private int randomPosition() {
     Random random = new Random();
     int position = random.nextInt(32 * 32);
     while (cells[position / 32][position % 32].getImage() != null) {
         position = random.nextInt(32 * 32);
     }
     return position;
 }

 public void saveBoard(String filePath) throws IOException {
	   try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filePath))) {
	       oos.writeObject(this.obstacleImage1Bytes);
	       oos.writeObject(this.obstacleImage2Bytes);
	       oos.writeObject(this.rewardImage1Bytes);
	       oos.writeObject(this.rewardImage2Bytes);
	       oos.writeObject(this.rewardImage3Bytes);
	       oos.writeObject(this.wallImageBytes);
	   }
	}

 public static Gameboard loadBoard(String filePath) throws IOException, ClassNotFoundException {
	   try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filePath))) {
	       byte[] obstacleImage1Bytes = (byte[]) ois.readObject();
	       byte[] obstacleImage2Bytes = (byte[]) ois.readObject();
	       byte[] rewardImage1Bytes = (byte[]) ois.readObject();
	       byte[] rewardImage2Bytes = (byte[]) ois.readObject();
	       byte[] rewardImage3Bytes = (byte[]) ois.readObject();
	       byte[] wallImageBytes = (byte[]) ois.readObject();
	       
	       Gameboard loadedGameboard = new Gameboard();
	       loadedGameboard.obstacleImage1 = loadedGameboard.convertBytesToImage(obstacleImage1Bytes);
	       loadedGameboard.obstacleImage2 = loadedGameboard.convertBytesToImage(obstacleImage2Bytes);
	       loadedGameboard.rewardImage1 = loadedGameboard.convertBytesToImage(rewardImage1Bytes);
	       loadedGameboard.rewardImage2 = loadedGameboard.convertBytesToImage(rewardImage2Bytes);
	       loadedGameboard.rewardImage3 = loadedGameboard.convertBytesToImage(rewardImage3Bytes);
	       loadedGameboard.wallImage = loadedGameboard.convertBytesToImage(wallImageBytes);
	       
	       return loadedGameboard;
	   }
	}

 public static void main(String[] args) {
	  JFrame mainFrame = new JFrame("Main");
	  mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	  mainFrame.setSize(800, 600); // Set the initial size of the window
      Gameboard gameboardInstance = new Gameboard();

	  // Create a JPanel for the buttons
	  JPanel buttonPanel = new JPanel();
	  buttonPanel.setLayout(new FlowLayout());
	  

	  // Create a JPanel for the right section
	  JPanel rightPanel = new JPanel(new BorderLayout());
	// Declare a variable to store the current Gameboard

	// Declare a variable to store the current Gameboard
	
	  JButton saveButton = new JButton("Save");
	  JButton designButton = new JButton("Design");
      designButton.addActionListener(new ActionListener() {
          @Override
          public void actionPerformed(ActionEvent e) {
              rightPanel.removeAll(); // Remove all components from the rightPanel
              gameboardInstance.currentGameboard = new Gameboard();
              rightPanel.add(gameboardInstance.currentGameboard, BorderLayout.CENTER);
              saveButton.setVisible(true);
              rightPanel.revalidate();
              rightPanel.repaint();
          }
      });
      buttonPanel.add(designButton);

    
      
      saveButton.setVisible(false); // Initially, the saveButton is not visible
      saveButton.addActionListener(new ActionListener() {
       @Override
       public void actionPerformed(ActionEvent e) {
         if (gameboardInstance.currentGameboard != null) {
           JFileChooser fileChooser = new JFileChooser();
           int returnValue = fileChooser.showSaveDialog(null);
           if (returnValue == JFileChooser.APPROVE_OPTION) {
             File selectedFile = fileChooser.getSelectedFile();
             try {
               gameboardInstance.currentGameboard.saveBoard(selectedFile.getPath());
             } catch (IOException ex) {
               ex.printStackTrace();
             }
           }
         }
       }
      });
      buttonPanel.add(saveButton);


      JButton loadButton = new JButton("Load");
      loadButton.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
          JFileChooser fileChooser = new JFileChooser();
          int returnValue = fileChooser.showOpenDialog(null);
          if (returnValue == JFileChooser.APPROVE_OPTION) {
              File selectedFile = fileChooser.getSelectedFile();
              try {
                  Gameboard loadedGameboard = Gameboard.loadBoard(selectedFile.getPath());
                  rightPanel.removeAll(); // Remove all components from the rightPanel
                  gameboardInstance.currentGameboard = loadedGameboard;
                  rightPanel.add(gameboardInstance.currentGameboard, BorderLayout.CENTER);
                  saveButton.setVisible(true);
                  rightPanel.revalidate();
                  rightPanel.repaint();
              } catch (IOException | ClassNotFoundException ex) {
                  ex.printStackTrace();
              }
          }
        }
      });
      buttonPanel.add(loadButton);

	  // Create a JSplitPane to divide the window into two sections
	  JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, buttonPanel, rightPanel);
	  splitPane.setDividerLocation(0.2); // Set the initial location of the divider

	  mainFrame.add(splitPane);
	  mainFrame.pack();
	  mainFrame.setVisible(true);
	}

}
interface DrawableInterface {
    void draw(Graphics g);
}

abstract class Drawable implements Serializable, DrawableInterface {
    protected transient BufferedImage image;
    protected byte[] imageBytes;
    private static final long serialVersionUID = 1L;

    public abstract void setImage(BufferedImage image);
    public abstract BufferedImage getImage();
    
    // Add a new abstract method
    public abstract void rotateImage(double angle);
}

abstract class GameObject extends Drawable {
    private static final long serialVersionUID = 1L;

    // Implement the abstract methods
    @Override
    public void setImage(BufferedImage image) {
        this.image = image;
        try {
            this.imageBytes = convertImageToBytes(image); // convert the image to a byte array
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        
        
    }
    

    @Override
    public BufferedImage getImage() {
        if (image == null && imageBytes != null) {
            // if the image is null and imageBytes is not null, convert imageBytes back to a BufferedImage
            try {
                image = convertBytesToImage(imageBytes);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return image;
    }
    protected byte[] convertImageToBytes(BufferedImage image) throws IOException {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ImageIO.write(image, "png", baos);
        return baos.toByteArray();
    }

    protected BufferedImage convertBytesToImage(byte[] imageBytes) throws IOException {
        ByteArrayInputStream bais = new ByteArrayInputStream(imageBytes);
        return ImageIO.read(bais);
    }
    @Override
    public void rotateImage(double angle) {
        // Implement image rotation logic
    }
    
    @Override
    public void draw(Graphics g) {
        // Implement drawing logic
    }
}
class Obstacle extends GameObject {
	   /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private BufferedImage image;

	   @Override
	   public void setImage(BufferedImage image) {
	       this.image = image;
	   }

	   @Override
	   public BufferedImage getImage() {
	       return this.image;
	   }

	@Override
	public byte[] convertImageToBytes(BufferedImage image) throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public BufferedImage convertBytesToImage(byte[] imageBytes) throws IOException {
		// TODO Auto-generated method stub
		return null;
	}
	}

	class Reward extends GameObject {
	   /**
		 * 
		 */
		private static final long serialVersionUID = 1L;
	private BufferedImage image;

	   @Override
	   public void setImage(BufferedImage image) {
	       this.image = image;
	   }

	   @Override
	   public BufferedImage getImage() {
	       return this.image;
	   }
	}

	class Cell implements Serializable {
		   private static final long serialVersionUID = 1L;
		   private GameObject[] objects;
		   private BufferedImage image;
		   private boolean hasReward;

		   public Cell() {
		       this.objects = new GameObject[5];
		   }

		   public void setObject(GameObject object, int position) {
		       if (position == 0 && !(object.getClass() == Reward.class || object.getClass() == Obstacle.class)) {
		           throw new IllegalArgumentException("Only rewards and obstacles can be placed in the center.");
		       }
		       this.objects[position] = object;
		       this.image = object.getImage();
		   }

		   public GameObject getObject(int position) {
			   if(position != 0) {
				   System.out.println("this is a wall!");
			   }
		       return this.objects[position];
		   }

		   public void setImage(BufferedImage image) {
		       this.image = image;
		   }

		   public BufferedImage getImage() {
		       return this.image;
		   }

		   public void setReward(Reward reward) {
		       this.objects[0] = reward;
		       this.hasReward = true;
		       this.image = reward.getImage();
		   }

		   public Reward getReward() {
		       return (Reward) this.objects[0];
		   }

		   public boolean hasReward() {
		       return this.hasReward;
		   }
		}

	class Wall extends Obstacle  {
		   private static final long serialVersionUID = 1L;
		   private BufferedImage images;

		   public Wall(BufferedImage images) {
		       this.images = images;
		   }

		   @Override
		   public void setImage(BufferedImage image) {
		       this.images = image;

		   }

		   @Override
		   public BufferedImage getImage() {
			   		return this.images;		   }
		}


