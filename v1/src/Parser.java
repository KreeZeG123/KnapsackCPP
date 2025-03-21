import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Objects;

public class Parser {
    public static void main(String[] args) throws IOException {
        File dossier = new File("kplib-master");

        if (dossier.exists() && dossier.isDirectory()) {
            String pathNewDossier = dossier.getName() + "_parsed";
            Files.createDirectories(Path.of(pathNewDossier)); // Crée le dossier principal "_parsed"

            // Parcourir les sous-dossiers du dossier principal
            File[] sousDossiers = Objects.requireNonNull(dossier.listFiles(File::isDirectory));
            for (File sousDossier : sousDossiers) {
                String pathNewSousDossier = pathNewDossier + "/" + sousDossier.getName();
                Files.createDirectories(Paths.get(pathNewSousDossier)); // Crée le sous-dossier

                // Parcourir les sous-dossiers de niveau 2
                File[] sousDossier2s = Objects.requireNonNull(sousDossier.listFiles(File::isDirectory));
                for (File sousDossier2 : sousDossier2s) {
                    String pathNewSousDossier2 = pathNewSousDossier + "/" + sousDossier2.getName();
                    Files.createDirectories(Paths.get(pathNewSousDossier2)); // Crée le sous-dossier 2

                    // Parcourir les sous-dossiers de niveau 3
                    File[] sousDossier3s = Objects.requireNonNull(sousDossier2.listFiles(File::isDirectory));
                    for (File sousDossier3 : sousDossier3s) {
                        String pathNewSousDossier3 = pathNewSousDossier2 + "/" + sousDossier3.getName();
                        Files.createDirectories(Paths.get(pathNewSousDossier3)); // Crée le sous-dossier 3

                        // Parcourir les fichiers dans le sous-dossier 3
                        File[] files = Objects.requireNonNull(sousDossier3.listFiles());
                        for (File file : files) {
                            Path parsedFilePath = Paths
                                    .get(pathNewSousDossier3 + "/" + file.getName().replaceAll(".kp", ".in"));
                            Files.createFile(parsedFilePath); // Crée le fichier

                            try (BufferedReader br = new BufferedReader(new FileReader(file));
                                    BufferedWriter bufferParsedFile = new BufferedWriter(
                                            new FileWriter(parsedFilePath.toFile()))) {

                                String line;
                                int numLigne = 0;
                                String sauvegardeBound = "";
                                String nbObjets = "";
                                ArrayList<String> values = new ArrayList<>();
                                ArrayList<String> weights = new ArrayList<>();
                                while ((line = br.readLine()) != null) {
                                    if (!line.trim().isEmpty()) {
                                        if (numLigne == 1) {
                                            nbObjets = line;
                                        } else if (numLigne == 2) {
                                            sauvegardeBound = line;
                                        } else {
                                            String[] valeur = line.split(" ");
                                            values.add(valeur[0]);
                                            weights.add(valeur[1]);
                                        }
                                    }
                                    numLigne++;
                                }
                                bufferParsedFile.write(nbObjets + "\n");
                                for (int i = 0; i < values.size(); i++) {
                                    bufferParsedFile.write(values.get(i) + " ");
                                }
                                bufferParsedFile.write("\n");
                                for (int i = 0; i < weights.size(); i++) {
                                    bufferParsedFile.write(values.get(i) + " ");
                                }
                                bufferParsedFile.write("\n");
                                bufferParsedFile.write(sauvegardeBound);
                            } catch (IOException e) {
                                System.err.println("Erreur lors de la lecture/écriture du fichier : " + file.getName());
                                e.printStackTrace();
                            }
                        }
                    }
                }
            }
        } else {
            System.out.println("Le dossier spécifié n'existe pas ou n'est pas un répertoire.");
        }
    }
}