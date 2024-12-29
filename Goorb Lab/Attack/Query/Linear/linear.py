import numpy as np

class BlackBox:
    def __init__(self, l, A):
        self.l = l
        self.A = A
    
    def query(self, block, mode='encrypt'):
        if mode == 'encrypt':
            return self.encrypt(block)
        else:
            return self.decrypt(block)
    
    def encrypt(self, plain_block):
        # Placeholder for encryption logic
        return np.random.randint(2, size=self.A)
    
    def decrypt(self, cipher_block):
        # Placeholder for decryption logic
        return np.random.randint(2, size=self.l)

class LinearCorrelationAttack:
    def __init__(self, black_box, initial_coins):
        self.black_box = black_box
        self.coins = initial_coins
    
    # Collect data using Linear Correlation Technique
    def collect_data(self, num_samples, bit_indices, cost_encrypt, cost_decrypt, action, mode='both'):
        X_plain = []
        Y_cipher = []
        for _ in range(num_samples):
            if self.coins <= 0:
                print("No more coins left. Terminating attack.")
                break
            if mode == 'encrypt' or (mode == 'both' and np.random.rand() < 0.5):
                if self.coins >= cost_encrypt:
                    plain_block = np.random.randint(2, size=self.black_box.l)
                    cipher_block = self.black_box.query(plain_block, mode='encrypt')
                    self.coins -= cost_encrypt
                else:
                    print("Not enough coins for encryption. Skipping this query.")
                    continue
            else:
                if self.coins >= cost_decrypt:
                    cipher_block = np.random.randint(2, size=self.black_box.A)
                    plain_block = self.black_box.query(cipher_block, mode='decrypt')
                    self.coins -= cost_decrypt
                else:
                    print("Not enough coins for decryption. Skipping this query.")
                    continue
            X_plain.append(plain_block)
            Y_cipher.append(cipher_block)
            differences = [cipher_block[j] != plain_block[j] for j in bit_indices]
            if any(differences):
                action(plain_block, cipher_block, differences)
        return np.array(X_plain), np.array(Y_cipher)
    
    # Analyze correlation using Linear Correlation Technique
    def analyze_correlation(self, X_plain, Y_cipher, bit_indices):
        num_samples = X_plain.shape[0]
        correlation_counts = np.zeros((self.l, self.A))
        for i in range(num_samples):
            plain_block = X_plain[i]
            cipher_block = Y_cipher[i]
            for j in bit_indices:
                correlation_counts[:, j] += plain_block == cipher_block[j]
        correlation = correlation_counts / num_samples
        return correlation
    
    # Estimate key using Linear Correlation Technique
    def estimate_key(self, correlation, threshold=0.5):
        key_estimates = np.argmax(correlation, axis=0) > threshold
        return key_estimates

def my_action(plain_block, cipher_block, differences):
    print(f"Difference found! Plain Block: {plain_block}, Cipher Block: {cipher_block}, Differences at bits: {differences}")

if __name__ == '__main__':
    # Parameters
    l = 8  # Length of plain block
    A = 8  # Length of cipher block
    initial_coins = 20  # Initial number of coins
    cost_encrypt = 2  # Cost of an encryption query
    cost_decrypt = 3  # Cost of a decryption query
    
    # Create instance of the Black Box
    black_box = BlackBox(l, A)
    
    # Create instance of the Linear Correlation Attack
    attack = LinearCorrelationAttack(black_box, initial_coins)
    
    # Collect data with specified action and mode
    num_samples = 10
    bit_indices = [0, 1, 2]  # For example, we check first three bits
    X_plain, Y_cipher = attack.collect_data(num_samples, bit_indices, cost_encrypt, cost_decrypt, my_action, mode='both')
    
    # Analyze correlation using Linear Correlation Technique
    correlation = attack.analyze_correlation(X_plain, Y_cipher, bit_indices)
    
    # Estimate key using Linear Correlation Technique
    key_estimates = attack.estimate_key(correlation)
    print(f"Estimated Key: {key_estimates}")