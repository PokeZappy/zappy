import numpy as np
import math


def calc_encryption_key(key: str) -> [[int]]:
    key_len = len(key)
    matrix_size = int(np.ceil(np.sqrt(key_len)))
    print(matrix_size)
    matrix = [
        [ord(key[count]) if count < key_len else 0 for count in range(i * matrix_size, (i + 1) * matrix_size)]
        for i in range(matrix_size)]

    return matrix


class Cipher(object):

    def __init__(self, key_str):
        self.key: [[int]] = calc_encryption_key(key_str)
        self.key_inv = np.linalg.inv(self.key)

    def message_matrix(self, message) -> list[list[int]]:
        matrix_size = len(self.key)
        msg_len = len(message)
        matrix = [
            [ord(message[count]) if count < msg_len else 0 for count in range(i * matrix_size, (i + 1) * matrix_size)]
            for i in range(math.ceil(msg_len / matrix_size))
        ]
        return matrix

    def calc_result_matrix(self, message_matrix) -> list[int]:
        result_matrix = [
            sum(message_matrix[i][k] * self.key[k][j] for k in range(len(self.key)))
            for i in range(len(message_matrix))
            for j in range(len(self.key))
        ]
        return result_matrix

    def encryption(self, message) -> list[int]:
        matrix_msg = self.message_matrix(message)
        resulting_matrix = self.calc_result_matrix(matrix_msg)
        return resulting_matrix

    def decryption(self, message: list[int]) -> str:
        message_matrix = np.array(message).reshape(-1, 10)
        decrypted_matrix = np.dot(message_matrix, self.key_inv)
        decrypted_matrix = np.round(decrypted_matrix).astype(int)
        decrypted_message = ''.join(chr(num) for row in decrypted_matrix for num in row if 32 <= num <= 126)
        return decrypted_message
