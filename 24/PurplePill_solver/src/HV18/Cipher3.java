package HV18;


import java.util.Arrays;

public class Cipher3 {
    public static final int KEYSTREAM_LENGTH = 16;
    public static final int IV_LENGTH = 8;
    private static final int[] A = new int[]{1295307597, -749914925, 886263092, 1295307597, -749914925, 886263092, 1295307597, -749914925};
    private final int[] X = new int[8];
    private final int[] C = new int[8];
    private byte b = 0;
    private int keyindex = 0;
    private byte[] keystream = null;

    private final int rotl(int value, int shift) {
        return value << shift | value >>> 32 - shift;
    }

    public byte[] crypt(byte[] message) {
        int index = 0;
        while (index < message.length) {
            if (this.keystream == null || this.keyindex == 16) {
                this.keystream = this.keyStream();
                this.keyindex = 0;
            }
            while (this.keyindex < 16 && index < message.length) {
                byte[] arrby = message;
                int n = index++;
                arrby[n] = (byte)(arrby[n] ^ this.keystream[this.keyindex]);
                ++this.keyindex;
            }
        }
        return message;
    }

    private byte[] keyStream() {
        this.nextState();
        byte[] s = new byte[16];
        int x = this.X[0] & 65535 ^ this.X[5] >>> 16;
        s[0] = (byte)(x & 255);
        s[1] = (byte)(x >> 8);
        x = this.X[3] & 65535 ^ this.X[0] >>> 16;
        s[2] = (byte)(x & 255);
        s[3] = (byte)(x >> 8);
        x = this.X[2] & 65535 ^ this.X[7] >>> 16;
        s[4] = (byte)(x & 255);
        s[5] = (byte)(x >> 8);
        x = this.X[5] & 65535 ^ this.X[2] >>> 16;
        s[6] = (byte)(x & 255);
        s[7] = (byte)(x >> 8);
        x = this.X[4] & 65535 ^ this.X[1] >>> 16;
        s[8] = (byte)(x & 255);
        s[9] = (byte)(x >> 8);
        x = this.X[7] & 65535 ^ this.X[4] >>> 16;
        s[10] = (byte)(x & 255);
        s[11] = (byte)(x >> 8);
        x = this.X[6] & 65535 ^ this.X[3] >>> 16;
        s[12] = (byte)(x & 255);
        s[13] = (byte)(x >> 8);
        x = this.X[1] & 65535 ^ this.X[6] >>> 16;
        s[14] = (byte)(x & 255);
        s[15] = (byte)(x >> 8);
        return s;
    }

    private void nextState() {
        int j = 0;
        while (j < 8) {
            long t = ((long)this.C[j] & 0xFFFFFFFFL) + ((long)A[j] & 0xFFFFFFFFL) + (long)this.b;
            this.b = (byte)(t >>> 32);
            this.C[j] = (int)(t & -1L);
            ++j;
        }
        int[] G = new int[8];
        int j2 = 0;
        while (j2 < 8) {
            long t = (long)(this.X[j2] + this.C[j2]) & 0xFFFFFFFFL;
            t *= t;
            G[j2] = (int)(t & -1L ^ t >>> 32);
            ++j2;
        }
        this.X[0] = G[0] + this.rotl(G[7], 16) + this.rotl(G[6], 16);
        this.X[1] = G[1] + this.rotl(G[0], 8) + G[7];
        this.X[2] = G[2] + this.rotl(G[1], 16) + this.rotl(G[0], 16);
        this.X[3] = G[3] + this.rotl(G[2], 8) + G[1];
        this.X[4] = G[4] + this.rotl(G[3], 16) + this.rotl(G[2], 16);
        this.X[5] = G[5] + this.rotl(G[4], 8) + G[3];
        this.X[6] = G[6] + this.rotl(G[5], 16) + this.rotl(G[4], 16);
        this.X[7] = G[7] + this.rotl(G[6], 8) + G[5];
    }

    public void reset() {
        this.b = 0;
        this.keyindex = 0;
        this.keystream = null;
        Arrays.fill(this.X, 0);
        Arrays.fill(this.C, 0);
    }

    public void setupIV(byte[] IV) {
        short[] sIV = new short[IV.length >> 1];
        int i = 0;
        while (i < sIV.length) {
            sIV[i] = (short)(IV[2 * i + 1] << 8 | (short)IV[2 * i] & 255);
            ++i;
        }
        this.setupIV(sIV);
    }

    public void setupIV(short[] iv) {
        int[] arrn = this.C;
        arrn[0] = arrn[0] ^ (iv[1] << 16 | iv[0] & 65535);
        int[] arrn2 = this.C;
        arrn2[1] = arrn2[1] ^ (iv[3] << 16 | iv[1] & 65535);
        int[] arrn3 = this.C;
        arrn3[2] = arrn3[2] ^ (iv[3] << 16 | iv[2] & 65535);
        int[] arrn4 = this.C;
        arrn4[3] = arrn4[3] ^ (iv[2] << 16 | iv[0] & 65535);
        int[] arrn5 = this.C;
        arrn5[4] = arrn5[4] ^ (iv[1] << 16 | iv[0] & 65535);
        int[] arrn6 = this.C;
        arrn6[5] = arrn6[5] ^ (iv[3] << 16 | iv[1] & 65535);
        int[] arrn7 = this.C;
        arrn7[6] = arrn7[6] ^ (iv[3] << 16 | iv[2] & 65535);
        int[] arrn8 = this.C;
        arrn8[7] = arrn8[7] ^ (iv[2] << 16 | iv[0] & 65535);
        this.nextState();
        this.nextState();
        this.nextState();
        this.nextState();
    }

    public void setupKey(byte[] key) {
        short[] sKey = new short[key.length >> 1];
        int i = 0;
        while (i < sKey.length) {
            sKey[i] = (short)(key[2 * i + 1] << 8 | (short)key[2 * i] & 255);
            ++i;
        }
        this.setupKey(sKey);
    }

    public void setupKey(short[] key) {
        this.X[0] = key[1] << 16 | key[0] & 65535;
        this.X[1] = key[6] << 16 | key[5] & 65535;
        this.X[2] = key[3] << 16 | key[2] & 65535;
        this.X[3] = key[0] << 16 | key[7] & 65535;
        this.X[4] = key[5] << 16 | key[4] & 65535;
        this.X[5] = key[2] << 16 | key[1] & 65535;
        this.X[6] = key[7] << 16 | key[6] & 65535;
        this.X[7] = key[4] << 16 | key[3] & 65535;
        this.C[0] = key[4] << 16 | key[5] & 65535;
        this.C[1] = key[1] << 16 | key[2] & 65535;
        this.C[2] = key[6] << 16 | key[7] & 65535;
        this.C[3] = key[3] << 16 | key[4] & 65535;
        this.C[4] = key[0] << 16 | key[1] & 65535;
        this.C[5] = key[5] << 16 | key[6] & 65535;
        this.C[6] = key[2] << 16 | key[3] & 65535;
        this.C[7] = key[7] << 16 | key[0] & 65535;
        this.nextState();
        this.nextState();
        this.nextState();
        this.nextState();
        int[] arrn = this.C;
        arrn[0] = arrn[0] ^ this.X[4];
        int[] arrn2 = this.C;
        arrn2[1] = arrn2[1] ^ this.X[5];
        int[] arrn3 = this.C;
        arrn3[2] = arrn3[2] ^ this.X[6];
        int[] arrn4 = this.C;
        arrn4[3] = arrn4[3] ^ this.X[7];
        int[] arrn5 = this.C;
        arrn5[4] = arrn5[4] ^ this.X[0];
        int[] arrn6 = this.C;
        arrn6[5] = arrn6[5] ^ this.X[1];
        int[] arrn7 = this.C;
        arrn7[6] = arrn7[6] ^ this.X[2];
        int[] arrn8 = this.C;
        arrn8[7] = arrn8[7] ^ this.X[3];
    }
}

