package HV18;

import HV18.Cipher3;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.OpenOption;


public class PurplePill {
	public static byte[] unhexlify(String ss) {
	    int strlen = ss.length();
	    if (strlen>0 && strlen%2!=0) {
	        throw new RuntimeException("odd-length string");
	    }
	    byte[] ret = new byte[strlen/2];
	    for (int i=0; i<strlen; i+=2) {
	        int a = Character.digit(ss.charAt(i),0x10);
	        int b = Character.digit(ss.charAt(i+1),0x10);
	        if (a==-1 || b==-1) {
	            throw new RuntimeException("non-hex digit");
	        }
	        ret[i/2] = (byte) ((a<<4)+b);
	    }
	    return ret;
	}
	
    public static void main(String[] args) throws IOException {
        if (args.length != 5) {
            System.out.println("java -jar purplepill.jar redpill_encrypted bluepill_encrypted redpill_code bluepill_code purple_pill.png \n");
            System.exit(0);
        }
        byte[] red_iv = args[2].getBytes();
        byte[] red_k = new byte[16];
        byte[] blue_iv = unhexlify(args[3]);
        byte[] blue_k = {(byte)0x87, (byte)0x05, (byte)0x89, (byte)0xCD, (byte)0xA8, (byte)0x75, (byte)0x62, (byte)0xEF, (byte)0x38, (byte)0x45, (byte)0xFF, (byte)0xD1, (byte)0x41, (byte)0x37, (byte)0x54, (byte)0xD5};
        
        System.arraycopy(red_iv, 0, red_k, 0, 8);
        System.arraycopy(red_iv, 0, red_k, 8, 8);
        
        byte[] redpill_ciphertext = Files.readAllBytes(new File(args[0]).toPath());
        byte[] bluepill_ciphertext = Files.readAllBytes(new File(args[1]).toPath());
        
        Cipher3 red_cipher = new Cipher3();
        System.out.println("Decrypting " + args[0] + " with k="+ new String(red_k, "UTF-8") + " iv=" +  new String(red_iv, "UTF-8"));
        red_cipher.setupKey(red_k);
        red_cipher.setupIV(red_iv);
        byte[] redpill_plaintext = red_cipher.crypt(redpill_ciphertext);
        //Files.write(new File(args[0] + "_decrypted").toPath(), redpill_plaintext, new OpenOption[0]);
        
        Cipher3 blue_cipher = new Cipher3();
        System.out.println("Decrypting " + args[1] + " with k="+ new String(blue_k, "UTF-8") + " iv=" +  new String(blue_iv, "UTF-8"));
        blue_cipher.setupKey(blue_k);
        blue_cipher.setupIV(blue_iv);
        byte[] bluepill_plaintext = blue_cipher.crypt(bluepill_ciphertext);
        //Files.write(new File(args[1] + "_decrypted").toPath(), bluepill_plaintext, new OpenOption[0]);
        
        byte[] purplepill = new byte[redpill_ciphertext.length * 2];
        int i = 0;
        while (i < purplepill.length) {
        	if (i%2 == 0) {
        		purplepill[i] = (byte) ((byte)(bluepill_plaintext[i / 2] & 0xf0) | (byte)((redpill_plaintext[i / 2] & 0xff) >> 4));
        	}
        	else {
        		purplepill[i] = (byte) ((byte)(bluepill_plaintext[i / 2] << 4) | (byte)(redpill_plaintext[i / 2] & 0x0f));
        	}
            ++i;
        }
        Files.write(new File(args[4]).toPath(), purplepill, new OpenOption[0]);
        
        
    }
}

